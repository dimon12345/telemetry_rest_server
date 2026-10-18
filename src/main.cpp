int main(int argc, char **argv) {
    try {
        ArgParseConfig config(argc, argv);
        return 0;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}