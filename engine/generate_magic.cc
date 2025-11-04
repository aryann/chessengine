#include <fstream>
#include <iostream>
#include <print>

int main(int argc, char** argv) {
  if (argc != 2) {
    std::println(std::cerr,
                 "Expected output file name as a single positional argument.");
    return 1;
  }

  std::string output_filename = argv[1];
  std::ofstream output(output_filename);

  if (!output.is_open()) {
    std::println(std::cerr, "Could not open output file: {}", output_filename);
    return 1;
  }

  std::println(output, "#ifndef CHESS_ENGINE_ENGINE_MAGIC_H_");
  std::println(output, "#define CHESS_ENGINE_ENGINE_MAGIC_H_");
  std::println(output);
  std::println(output, "#include \"engine/attacks.h\"");
  std::println(output);
  std::println(output, "namespace chessengine {{");

  std::println(output, "}}  // namespace chessengine");
  std::println(output);
  std::println(output, "#endif  // CHESS_ENGINE_ENGINE_MAGIC_H_");

  output.close();
  return 0;
}