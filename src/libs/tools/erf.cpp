/*
 * Copyright (c) 2020-2023 The reone project contributors
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

#include "reone/tools/erf.h"

#include "reone/resource/format/erfwriter.h"
#include "reone/resource/typeutil.h"
#include "reone/system/stream/fileinput.h"

using namespace reone::resource;

namespace reone {

void ErfTool::invoke(Operation operation, const std::filesystem::path &input, const std::filesystem::path &outputDir, const std::filesystem::path &gamePath) {
    switch (operation) {
    case Operation::List:
    case Operation::Extract: {
        auto stream = FileInputStream(input);
        ErfReader erf(stream);
        erf.load();
        if (operation == Operation::Extract) {
            extract(erf, input, outputDir);
        } else {
            list(erf);
        }
        break;
    }
    case Operation::ToERF:
    case Operation::ToMOD:
        toERF(operation, input, outputDir);
        break;
    }
}

void ErfTool::list(const ErfReader &erf) {
    for (auto &key : erf.keys()) {
        std::cout << key.resId.string() << std::endl;
    }
}

void ErfTool::extract(ErfReader &erf, const std::filesystem::path &erfPath, const std::filesystem::path &destPath) {
    if (!std::filesystem::exists(destPath)) {
        // Create destination directory if it does not exist
        std::filesystem::create_directory(destPath);
    } else if (!std::filesystem::is_directory(destPath)) {
        // Return if destination exists, but is not a directory
        return;
    }

    for (size_t i = 0; i < erf.keys().size(); ++i) {
        auto &key = erf.keys()[i];
        auto &erfResource = erf.resources()[i];
        debug("Extracting " + key.resId.string());

        auto buffer = ByteBuffer(erfResource.size, '\0');
        auto erf = FileInputStream(erfPath);
        erf.seek(erfResource.offset, SeekOrigin::Begin);
        erf.read(&buffer[0], buffer.size());

        auto resPath = destPath;
        auto &ext = getExtByResType(key.resId.type);
        resPath.append(key.resId.resRef + "." + ext);

        auto res = std::ofstream(resPath, std::ios::binary);
        res.write(&buffer[0], buffer.size());
    }
}

void ErfTool::toERF(Operation operation, const std::filesystem::path &target, const std::filesystem::path &destPath) {
    ErfWriter erf;

    for (auto &entry : std::filesystem::directory_iterator(target)) {
        std::filesystem::path path(entry);
        if (std::filesystem::is_directory(path))
            continue;

        std::string ext(path.extension().string());
        ext.erase(0, 1);

        ResourceType resType = getResTypeByExt(ext, false);
        if (resType == ResourceType::Invalid)
            continue;

        std::ifstream in(path, std::ios::binary);
        in.seekg(0, std::ios::end);
        size_t size = in.tellg();
        ByteBuffer data(size, '\0');
        in.seekg(0);
        in.read(&data[0], size);

        std::filesystem::path resRef(path.filename());
        resRef.replace_extension("");

        ErfWriter::Resource res;
        res.resRef = resRef.string();
        res.resType = resType;
        res.data = std::move(data);

        erf.add(std::move(res));
    }

    ErfWriter::FileType type;
    std::string ext;

    if (operation == Operation::ToMOD) {
        type = ErfWriter::FileType::MOD;
        ext = ".mod";
    } else {
        type = ErfWriter::FileType::ERF;
        ext = ".erf";
    }

    auto erfPath = destPath;
    erfPath.append(target.filename().string() + ext);
    erf.save(type, erfPath);
}

bool ErfTool::supports(Operation operation, const std::filesystem::path &input) const {
    switch (operation) {
    case Operation::List:
    case Operation::Extract: {
        std::string ext(input.extension().string());
        return !std::filesystem::is_directory(input) &&
               (ext == ".erf" || ext == ".mod" || ext == ".sav");
    }
    case Operation::ToERF:
    case Operation::ToMOD:
        return std::filesystem::is_directory(input);

    default:
        return false;
    }
}

} // namespace reone
