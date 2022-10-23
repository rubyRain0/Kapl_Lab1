#include "My_List.h"

bool task(LIST& list)
{
	auto one_parity = [](int* x, int* y)
	{
		return(*x + *y) % 2 == 0;
	};
	ptrNODE beg = nullptr, end = nullptr, head = list.get_head(), tail = list.get_tail();
	ptrNODE p = head;
	while (p->next && p->next->next)
	{
		if (one_parity(p->next->info, p->next->next->info))
		{
			beg = p;
			end = beg->next->next;
			break;
		}
		p = p->next;
	}
	if (beg)
	{
		std::cout << "\nPair Found: \n" << *(beg->next->info) << ' ' << *(end->info) << '\n';
		if (beg != head)
		{
			ptrNODE tmp = end->next;
			end->next = head->next;
			head->next = beg->next;
			beg->next = tmp;
			if (end == list.get_tail())
				list.set_tail(beg);
		}
	}
	else std::cout << "\nPair not found...\n";
	return beg;
}
int main()
{
	LIST list;
	std::ifstream file("data.txt");
	std::ofstream fileResult("dataResult.txt");
	bool stop = false;
	int option;
	while (!stop)
	{
		if (!file)
		{
			std::cout << "Input file not found...\n";
			break;
		}
		else
		{
			do
			{
				if (std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
				std::cout << "Type '1' - to create list by queue\nType '2' - to create list by stack\n"
					"Type '3' - to create list by order\n";
				std::cin >> option;
				switch (option)
				{
				case 1:
				{
					list.create_by_queue(file);
					break;
				}
				case 2:
				{
					list.create_by_stack(file);
					break;
				}
				case 3:
				{
					list.create_by_order(file);
					break;
				}
				default:
				{
					std::cout << "Incorrect input... Please input an integer/correct number!\n";
					break;
				}
				}
			} while (option > 3 || option < 1);
			if (list.get_size() <= 1)
			{
				std::cout << "List should have at least 2 elements!\n";
				fileResult << "No/not enough elements in the list!\n";
			}
			else
			{
				std::cout << "List before sorting: \n";
				list.print(); std::cout << '\n';
				do
				{
					if (std::cin.fail())
					{
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
					std::cout << "Sort the list?\n'1'-Yes\n'2'-No\n";
					std::cin >> option;
					switch (option)
					{
					case 1:
					{
						list.sorting();
						std::cout << "List after sorting: \n";
						list.print();
						break;
					}
					case 2:
					{
						break;
					}
					default:
					{
						std::cout << "Incorrect input... Please input an integer/correct number!\n";
						break;
					}
					}
				} while (option > 2 || option < 1);
				if (task(list))
					list.print(fileResult);
			}
			do
			{
				if (std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
				std::cout << "Continue?\n'1'-Yes\n'2'-Stop\n";
				std::cin >> option;
				switch (option)
				{
				case 1:
				{
					list.clear();
					file.seekg(0);
					fileResult << '\n';
					break;
				}
				case 2:
				{
					stop = true;
					break;
				}
				default:
				{
					std::cout << "Incorrect input... Please input an integer/correct number!\n";
					break;
				}
				}
			} while (option > 2 || option < 1);
		}
	}

	file.close();
	fileResult.close();

	std::cin.get();
}