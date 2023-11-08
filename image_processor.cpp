#include "ParseAndHelp.h"

int main(int argc, char** argv) {
    if (argc == 1) {
        PrintHelp();
        return -1;
    }
    if (argc == 2) {
        std::cerr << "Invalid arguments: input and output files missed";
        return -1;
    }

    std::string_view input_path = static_cast<std::string_view>(argv[1]);
    std::string_view output_path = static_cast<std::string_view>(argv[2]);

    try {
        Image img(input_path);
        std::cout << "Successfully read the file" << input_path << std::endl;

        CompositeFilter filters_to_apply({});
        ParsedToFilters(argc, argv, filters_to_apply);
        filters_to_apply.ApplyFilter(img);

        img.BMPWriteFile(output_path);
        std::cout << "Successfully wrote to the file " << output_path << std::endl;
    } catch (std::logic_error& e) {
        std::cerr << e.what() << std::endl;
        std::cerr << " Read instruction:" << std::endl;
        PrintHelp();
        return -1;
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    return 0;
}