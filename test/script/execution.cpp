/*
 * Copyright (c) 2020-2022 The reone project contributors
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <boost/test/unit_test.hpp>

#include "../../script/execution.h"
#include "../../script/executioncontext.h"
#include "../../script/program.h"

#include "../fixtures/script.h"

using namespace std;

using namespace reone;
using namespace reone::script;

BOOST_AUTO_TEST_SUITE(script_execution)

BOOST_AUTO_TEST_CASE(should_run_script_program__degenerate) {
    // given
    auto program = make_shared<ScriptProgram>("some_program");
    auto context = make_unique<ExecutionContext>();
    auto execution = ScriptExecution(program, move(context));

    // when
    auto result = execution.run();

    // then
    BOOST_CHECK_EQUAL(-1, result);
}

BOOST_AUTO_TEST_CASE(should_run_script_program__math) {
    // given
    auto program = make_shared<ScriptProgram>("some_program");
    program->add(Instruction::newCONSTI(-3));
    program->add(Instruction(InstructionType::NEGI));
    program->add(Instruction::newCONSTI(2));
    program->add(Instruction(InstructionType::MODII)); // 1
    program->add(Instruction::newCONSTF(2.0f));
    program->add(Instruction(InstructionType::ADDIF)); // 3.0
    program->add(Instruction::newCONSTI(3));
    program->add(Instruction(InstructionType::ADDFI)); // 6.0
    program->add(Instruction::newCONSTF(4.0f));
    program->add(Instruction(InstructionType::ADDFF)); // 10.0
    program->add(Instruction::newCONSTI(5));
    program->add(Instruction::newCONSTI(6));
    program->add(Instruction(InstructionType::SUBII)); // 10.0, -1
    program->add(Instruction(InstructionType::SUBFI)); // 11.0
    program->add(Instruction::newCONSTF(7.0f));
    program->add(Instruction(InstructionType::SUBFF)); // 4.0
    program->add(Instruction::newCONSTI(8));
    program->add(Instruction::newCONSTI(9));
    program->add(Instruction(InstructionType::MULII)); // 4.0, 72
    program->add(Instruction::newCONSTF(0.1f));
    program->add(Instruction(InstructionType::MULIF)); // 4.0, 7.2
    program->add(Instruction(InstructionType::MULFF)); // 28.8
    program->add(Instruction::newCONSTI(4));
    program->add(Instruction::newCONSTI(2));
    program->add(Instruction(InstructionType::DIVII)); // 28.8, 2
    program->add(Instruction::newCONSTF(1.0f));
    program->add(Instruction(InstructionType::DIVIF)); // 28.8, 2.0
    program->add(Instruction(InstructionType::DIVFF)); // 14.4
    program->add(Instruction(InstructionType::NEGF)); // -14.4
    program->add(Instruction::newCONSTF(-14.4f));
    program->add(Instruction(InstructionType::EQUALFF));

    auto context = make_unique<ExecutionContext>();
    auto execution = ScriptExecution(program, move(context));

    // when
    auto result = execution.run();

    // then
    BOOST_CHECK_EQUAL(1, result);
}

BOOST_AUTO_TEST_CASE(should_run_script_program__loop) {
    // given
    auto program = make_shared<ScriptProgram>("some_program");
    program->add(Instruction::newCONSTI(0));
    program->add(Instruction::newCONSTI(10));
    program->add(Instruction::newCPTOPSP(-8, 8));
    program->add(Instruction(InstructionType::LTII));
    program->add(Instruction::newJZ(18));
    program->add(Instruction::newINCISP(-8));
    program->add(Instruction::newJMP(-22));
    program->add(Instruction::newMOVSP(-4));
    program->add(Instruction(InstructionType::RETN));

    auto context = make_unique<ExecutionContext>();
    auto execution = ScriptExecution(program, move(context));

    // when
    auto result = execution.run();

    // then
    BOOST_CHECK_EQUAL(10, result);
}

BOOST_AUTO_TEST_CASE(should_run_script_program__action) {
    // given
    auto program = make_shared<ScriptProgram>("some_program");
    program->add(Instruction::newCONSTI(1));
    program->add(Instruction::newCONSTS("some_tag"));
    program->add(Instruction::newACTION(0, 2));

    auto routine = make_shared<MockRoutine>(
        "SomeAction",
        VariableType::Object,
        Variable::ofObject(kObjectInvalid),
        vector<VariableType> {VariableType::String, VariableType::Int});

    auto routines = MockRoutines();
    routines.add(0, routine);

    auto context = make_unique<ExecutionContext>();
    context->routines = &routines;

    auto execution = ScriptExecution(program, move(context));

    // when
    auto result = execution.run();

    // then
    BOOST_CHECK_EQUAL(-1, result);
    BOOST_CHECK_EQUAL(1ll, routine->invokeInvocations().size());
    auto &invocation = routine->invokeInvocations();
    BOOST_CHECK_EQUAL(string("some_tag"), get<0>(invocation[0])[0].strValue);
    BOOST_CHECK_EQUAL(1, get<0>(invocation[0])[1].intValue);
}

BOOST_AUTO_TEST_CASE(should_run_script_program__action_with_vectors) {
    // given
    auto program = make_shared<ScriptProgram>("some_program");
    program->add(Instruction::newCONSTI(1));
    program->add(Instruction::newCONSTF(2.0f));
    program->add(Instruction::newCONSTF(3.0f));
    program->add(Instruction::newCONSTF(4.0f));
    program->add(Instruction::newACTION(0, 2));
    program->add(Instruction(InstructionType::MULFF));
    program->add(Instruction(InstructionType::ADDFF));
    program->add(Instruction::newCONSTF(37.0f));
    program->add(Instruction(InstructionType::EQUALFF));

    auto routine = make_shared<MockRoutine>(
        "SomeAction",
        VariableType::Vector,
        Variable::ofVector(glm::vec3(5.0f, 6.0f, 7.0f)),
        vector<VariableType> {VariableType::Vector, VariableType::Int});

    auto routines = MockRoutines();
    routines.add(0, routine);

    auto context = make_unique<ExecutionContext>();
    context->routines = &routines;

    auto execution = ScriptExecution(program, move(context));

    // when
    auto result = execution.run();

    // then
    BOOST_CHECK_EQUAL(1, result);
    BOOST_CHECK_EQUAL(1ll, routine->invokeInvocations().size());
    auto &invocation = routine->invokeInvocations();
    auto inVecValue = get<0>(invocation[0])[0].vecValue;
    BOOST_CHECK_CLOSE(2.0f, inVecValue.x, 1e-5);
    BOOST_CHECK_CLOSE(3.0f, inVecValue.y, 1e-5);
    BOOST_CHECK_CLOSE(4.0f, inVecValue.z, 1e-5);
    BOOST_CHECK_EQUAL(1, get<0>(invocation[0])[1].intValue);
}

BOOST_AUTO_TEST_CASE(should_run_script_program__globals) {
    // given
    auto program = make_shared<ScriptProgram>("some_program");
    program->add(Instruction(InstructionType::RSADDI));
    program->add(Instruction::newCONSTI(42));
    program->add(Instruction::newCONSTF(1.0f));
    program->add(Instruction::newCONSTS("some_res_ref"));
    program->add(Instruction::newCONSTO(2));
    program->add(Instruction(InstructionType::SAVEBP));
    program->add(Instruction::newCONSTI(1));
    program->add(Instruction::newCPTOPBP(-16, 4));
    program->add(Instruction::newCPDOWNBP(-20, 4));
    program->add(Instruction::newMOVSP(-30));

    auto context = make_unique<ExecutionContext>();

    auto execution = ScriptExecution(program, move(context));

    // when
    auto result = execution.run();

    // then
    BOOST_CHECK_EQUAL(42, result);
}

BOOST_AUTO_TEST_CASE(should_run_script_program__subroutine) {
    // given
    auto program = make_shared<ScriptProgram>("some_program");
    program->add(Instruction(InstructionType::RSADDI));
    program->add(Instruction::newCONSTI(21));
    program->add(Instruction::newJSR(8));
    program->add(Instruction(InstructionType::RETN));
    program->add(Instruction::newCPTOPSP(-4, 4));
    program->add(Instruction::newCPTOPSP(-4, 4));
    program->add(Instruction(InstructionType::ADDII));
    program->add(Instruction::newCPDOWNSP(-12, 4));
    program->add(Instruction::newMOVSP(-8));
    program->add(Instruction(InstructionType::RETN));

    auto context = make_unique<ExecutionContext>();

    auto execution = ScriptExecution(program, move(context));

    // when
    auto result = execution.run();

    // then
    BOOST_CHECK_EQUAL(42, result);
}

BOOST_AUTO_TEST_CASE(should_run_script_program__vector_math) {
    // given
    auto program = make_shared<ScriptProgram>("some_program");
    program->add(Instruction::newCONSTF(1.0f));
    program->add(Instruction::newCONSTF(2.0f));
    program->add(Instruction::newCONSTF(3.0f));
    program->add(Instruction::newCONSTF(4.0f));
    program->add(Instruction::newCONSTF(5.0f));
    program->add(Instruction::newCONSTF(6.0f));
    program->add(Instruction(InstructionType::ADDVV)); // [5.0, 7.0, 9.0]
    program->add(Instruction(InstructionType::ADDFF)); // 5.0, 16.0
    program->add(Instruction(InstructionType::ADDFF)); // 21.0
    program->add(Instruction::newCONSTF(7.0f));
    program->add(Instruction::newCONSTF(8.0f));
    program->add(Instruction::newCONSTF(9.0f));
    program->add(Instruction::newCONSTF(3.0f));
    program->add(Instruction::newCONSTF(2.0f));
    program->add(Instruction::newCONSTF(1.0f));
    program->add(Instruction(InstructionType::SUBVV)); // 21.0, [4.0, 6.0, 8.0]
    program->add(Instruction(InstructionType::ADDFF)); // 21.0, 4.0, 14.0
    program->add(Instruction(InstructionType::ADDFF)); // 21.0, 18.0
    program->add(Instruction(InstructionType::ADDFF)); // 39.0
    program->add(Instruction::newCONSTF(4.0f));
    program->add(Instruction::newCONSTF(5.0f));
    program->add(Instruction::newCONSTF(6.0f));
    program->add(Instruction(InstructionType::MULFV)); // [156.0, 195.0, 234.0]
    program->add(Instruction::newCONSTF(7.0f));
    program->add(Instruction(InstructionType::MULVF)); // [1092.0, 1365.0, 1638.0]
    program->add(Instruction(InstructionType::ADDFF)); // 1092.0, 3003.0
    program->add(Instruction(InstructionType::ADDFF)); // 4095.0
    program->add(Instruction::newCONSTF(1.0f));
    program->add(Instruction::newCONSTF(2.0f));
    program->add(Instruction::newCONSTF(3.0f));
    program->add(Instruction(InstructionType::DIVFV)); // [4095.0, 2047.5, 1365.0]
    program->add(Instruction::newCONSTF(0.5f));
    program->add(Instruction(InstructionType::DIVVF)); // [8190.0, 4095.0, 2730.0]
    program->add(Instruction(InstructionType::ADDFF)); // 8190.0, 6825.0
    program->add(Instruction(InstructionType::ADDFF)); // 15015.0
    program->add(Instruction::newCONSTF(15015.0f));
    program->add(Instruction(InstructionType::EQUALFF));

    auto context = make_unique<ExecutionContext>();
    auto execution = ScriptExecution(program, move(context));

    // when
    auto result = execution.run();

    // then
    BOOST_CHECK_EQUAL(1, result);
}

BOOST_AUTO_TEST_CASE(should_run_script_program__structs) {
    // given
    auto program = make_shared<ScriptProgram>("some_program");
    program->add(Instruction::newCONSTI(1));
    program->add(Instruction::newCONSTF(2.0f));
    program->add(Instruction::newCONSTS("some_resref"));
    program->add(Instruction::newCONSTO(3));
    program->add(Instruction::newCPTOPSP(-16, 16));
    program->add(Instruction::newEQUALTT(16)); // 1
    program->add(Instruction::newCONSTI(1));
    program->add(Instruction::newCONSTF(2.0f));
    program->add(Instruction::newCONSTS("some_resref"));
    program->add(Instruction::newCONSTO(3));
    program->add(Instruction::newCONSTI(1));
    program->add(Instruction::newCPTOPSP(-20, 16));
    program->add(Instruction::newDESTRUCT(16, 4, 8));
    program->add(Instruction::newCONSTO(3));
    program->add(Instruction::newEQUALTT(16)); // 1, 1
    program->add(Instruction::newCONSTI(1));
    program->add(Instruction::newCONSTF(2.0f));
    program->add(Instruction::newCONSTI(1));
    program->add(Instruction::newCONSTF(3.0f));
    program->add(Instruction::newNEQUALTT(8)); // 1, 1, 1
    program->add(Instruction(InstructionType::ADDII));
    program->add(Instruction(InstructionType::ADDII));
    program->add(Instruction::newCONSTI(3));
    program->add(Instruction(InstructionType::EQUALII));

    auto context = make_unique<ExecutionContext>();
    auto execution = ScriptExecution(program, move(context));

    // when
    auto result = execution.run();

    // then
    BOOST_CHECK_EQUAL(1, result);
}

BOOST_AUTO_TEST_SUITE_END()
