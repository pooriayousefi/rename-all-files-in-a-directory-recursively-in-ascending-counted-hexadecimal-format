
#include "C++ArmyKnife/literals.hpp"
#include "C++ArmyKnife/filesystem.hpp"
#include "C++ArmyKnife/chrono.hpp"
auto main()->int
{
	try
	{
		std::wcout << "\n Please, enter the path which you want to rename its files recursively in ascending counted hexadecimal format:\n ";
		std::wstring line{};
		std::getline(std::wcin, line);
		std::filesystem::path dirpath(line);
		auto counter{ 0_sz };
		apply_to_all_items_in_a_directory_recursively(
			[&counter](std::filesystem::path p)
			{
				if (std::filesystem::is_regular_file(p))
				{
					std::wstring c{ L"" };
					convert_decimal_to_hexadecimal(counter++, c);
					if (p.has_extension())
						std::filesystem::rename(p, p.parent_path() / std::filesystem::path(c + p.extension().wstring()));
					else
						std::filesystem::rename(p, p.parent_path() / std::filesystem::path(c));
				}
			},
			dirpath
		);
		std::wcout 
			<< "\n It's done. The program will be terminated in 5 seconds. T-"
			<< []() { countdown(5, [](int t) { std::cout << t << ' '; }); return ' '; }();		
		return EXIT_SUCCESS;
	}
	catch (const std::exception& xxx)
	{
		std::cerr
			<< "\n ERROR DETECTED!\n"
			<< xxx.what()
			<< "\n The program will be terminated in 5 seconds. T-" 
			<< []() { countdown(5, [](int t) { std::cout << t << ' '; }); return ' '; }();
		return EXIT_FAILURE;
	}
}