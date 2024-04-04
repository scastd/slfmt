#ifndef SLFMT_FILES_H
#define SLFMT_FILES_H

#include <filesystem>
#include <fmt/format.h>
#include <miniz.h>
#include <fstream>

namespace fs = std::filesystem;

namespace slfmt {
    class Files {
    public:
        /**
         * @brief Copies a file to the specified directory.
         *
         * @param filePath The path to the file to copy.
         * @param directory The directory to copy the file to.
         */
        static void CopyFileToDir(const fs::path &filePath, const fs::path &directory) {
            if (!fs::exists(filePath)) {
                throw std::runtime_error("Source file does not exist.");
            }

            fs::path dest = directory / filePath.filename();
            fs::copy_file(filePath, dest, fs::copy_options::overwrite_existing);
        }

        /**
         * @brief Moves a file to the specified directory.
         *
         * @param filePath The path to the file to move.
         * @param directory The directory to move the file to.
         */
        static void MoveFileToDir(const fs::path &filePath, const fs::path &directory) {
            if (!fs::exists(filePath)) {
                throw std::runtime_error("Source file does not exist.");
            }

            fs::path dest = directory / filePath.filename();
            fs::rename(filePath, dest);
        }

        /**
         * @brief Compresses a file into a zip archive.
         *
         * @param file The file to compress.
         * @param name The name of the zip archive.
         *
         * @return The path to the zip archive.
         */
        static fs::path CompressFile(const fs::path &file, const std::string &name) {
            const auto fileStr = file.string();
            const auto zipFilename = fmt::format("{}.zip", name);
            mz_zip_archive zip{};

            memset(&zip, 0, sizeof(zip));
            mz_zip_writer_init_file(&zip, zipFilename.c_str(), 0);

            mz_zip_writer_add_file(&zip, fileStr.c_str(), fileStr.c_str(), "", 0, MZ_BEST_COMPRESSION);

            mz_zip_writer_finalize_archive(&zip);
            mz_zip_writer_end(&zip);

            return zipFilename;
        }

        /**
         * @brief Clears the contents of the specified file.
         *
         * @param file The file to clear.
         */
        static void ClearFile(const fs::path &file) {
            std::ofstream ofs(file, std::ios::out | std::ios::trunc);
            ofs.close();
        }
    };
} // slfmt

#endif // SLFMT_FILES_H
