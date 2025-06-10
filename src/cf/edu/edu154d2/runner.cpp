#include <bits/stdc++.h>

namespace fs = std::filesystem;

using LL = long long;

const std::vector<std::string> process_paths = {"/home/laceprndpm/acm/src/cf/r154d2/C_friend.cpp",
                                                "/home/laceprndpm/acm/src/cf/r154d2/C.cpp"};
const fs::path                 gene_path     = "/home/laceprndpm/acm/src/cf/r154d2/gene.cpp";
constexpr int                  num_processes = 2;

std::optional<std::string> compile_program(const fs::path &output_path, const fs::path &source_path,
                                           const std::string &flags = "")
{
    std::string command = "g++ -O2 -w -o " + output_path.string() + " " + source_path.string() + " " + flags;
    if (system(command.c_str()) != 0) {
        return {};
    }
    return output_path.string();
}

void generate_data(const std::string &program_path, const std::string &seed, const std::string &data)
{
    std::string command = program_path + " " + seed + " " + data;
    system(command.c_str());
}

void run_program(const std::string &program_path, const std::string &input, const std::string &output)
{
    std::string command = "timeout 2s " + program_path + " " + input + " " + output;
    system(command.c_str());
}

bool compare_files(const fs::path &file1, const fs::path &file2)
{
    std::string command = "diff -ZB " + file1.string() + " " + file2.string();
    return system(command.c_str()) == 0;
}

void setup_directory(const fs::path &dir_name)
{
    fs::create_directory(dir_name);
}

void compile_all_programs(const fs::path &dir_name)
{
    for (int i = 0; i < num_processes; ++i) {
        fs::path program_name = "p" + std::to_string(i) + ".test";
        fs::path output_path  = dir_name / program_name;
        if (!compile_program(output_path, process_paths[i], "-DBATCH")) {
            throw std::runtime_error("Compilation failed : " + process_paths[i]);
        }
    }
    if (!compile_program(dir_name / "gene.test", gene_path, "-DBATCH")) {
        throw std::runtime_error("Compilation failed : " + gene_path.string());
    }
}

void run_all_programs(const fs::path &dir_name)
{
    fs::path input_path = dir_name / "test.in";

    generate_data((dir_name / "gene.test").string(), dir_name / "seed.txt", input_path);

    for (int i = 0; i < num_processes; ++i) {
        fs::path program_name        = "p" + std::to_string(i) + ".test";
        fs::path program_output_path = dir_name / (std::to_string(i) + ".out");
        run_program((dir_name / program_name).string(), input_path.string(), program_output_path.string());
    }
}

int compare_all_outputs(const fs::path &dir_name)
{
    for (int i = 0; i < num_processes - 1; ++i) {
        fs::path file1 = dir_name / (std::to_string(i) + ".out");
        fs::path file2 = dir_name / (std::to_string(i + 1) + ".out");
        if (!compare_files(file1, file2)) {
            return -1;
        }
    }
    return 0;
}

void helperFunction(int idx, int cnt)
{
    fs::path dir_name = "process_" + std::to_string(idx);
    dir_name          = fs::current_path() / dir_name;
    setup_directory(dir_name);
    compile_all_programs(dir_name);

    while (cnt > 0) {
        run_all_programs(dir_name);
        int result = compare_all_outputs(dir_name);
        if (result != 0) {
            std::string info = "Caughted BUG at p" + std::to_string(idx);
            // throw std::runtime_error(info);
            std::cout << info << '\n';
            return;
        }
        --cnt;
    }
    printf("Thread %d has done!\n", idx);
}

int main()
{
    const int                num_threads = 6;  // 你可以根据需要调整线程的数量
    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(helperFunction, i,
                             1000);  // 假设你仍然想要运行1000次
        // 第一次运行需要由time(0)初始化，之后则可以注释掉
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    for (auto &t : threads) {
        t.join();
    }
    return EXIT_SUCCESS;
}
