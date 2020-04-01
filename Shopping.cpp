#include <iostream>
#include <string>
#include <conio.h>
#include <cstdio>
#include <sstream>

using namespace std;

/*
Node Declaration
*/
struct product
{
	string name, category, brand;
	float price;
	int number;
	product *left, *right;
}*NameSortRoot, *PriceSortRoot, *NumberSortRoot;

/*
Class Declaration
*/
class storehouse
{
private:
	int max(int a, int b) { return (a > b) ? a : b; }
	int diff(product *CurProduct) { return height(CurProduct->left) - height(CurProduct->right); }
	int height(product *CurProduct) { return (CurProduct) ? max(height(CurProduct->left), height(CurProduct->right)) + 1 : 0; }
	product* balance_product(product *);
	account* balance_account(account *);
	product* RR_rotation(product *);
	product* LL_rotation(product *);
	product* LR_rotation(product *);
	product* RL_rotation(product *);
	product* Successor(product *);
	product* NameSort_Search(product *, string);
	product* PriceSort_Search(product *, int);
	product* NumberSort_Search(product *, int);

public:
	product* NameSort_Insert(product *, string, string, string, float, int);
	product* PriceSort_Insert(product *, string, string, string, float, int);
	product* NumberSort_Insert(product *, string, string, string, float, int);
	void InorderPrint(product *);
	void NameSort_SearchPrint(product *, string);
	void PriceSort_SearchPrint(product *, int);
	void NumberSort_SearchPrint(product *, int);
	product* NameSort_Delete(product *, string);
	product* PriceSort_Delete(product *, int);
	product* NumberSort_Delete(product *, int);

	account* NameSort_Insert_account(account *, string, int, float, int);
};

/*
Right- Right Rotation
*/
product *storehouse::RR_rotation(product *parent)
{
	product *temp;
	temp = parent->right;
	parent->right = temp->left;
	temp->left = parent;
	return temp;
}
/*
Left- Left Rotation
*/
product *storehouse::LL_rotation(product *parent)
{
	product *temp;
	temp = parent->left;
	parent->left = temp->right;
	temp->right = parent;
	return temp;
}

/*
Left - Right Rotation
*/
product *storehouse::LR_rotation(product *parent)
{
	product *temp;
	temp = parent->left;
	parent->left = RR_rotation(temp);
	return LL_rotation(parent);
}

/*
Right- Left Rotation
*/
product *storehouse::RL_rotation(product *parent)
{
	product *temp;
	temp = parent->right;
	parent->right = LL_rotation(temp);
	return RR_rotation(parent);
}

/*
Balancing AVL Tree
*/
product *storehouse::balance_product(product *CurProduct)
{
	int balance_factor = diff(CurProduct);

	if (balance_factor > 1)
	{
		if (diff(CurProduct->left) > 0)
			CurProduct = LL_rotation(CurProduct);
		else
			CurProduct = LR_rotation(CurProduct);
	}
	else if (balance_factor < -1)
	{
		if (diff(CurProduct->right) > 0)
			CurProduct = RL_rotation(CurProduct);
		else
			CurProduct = RR_rotation(CurProduct);
	}
	return CurProduct;
}

account *storehouse::balance_account(account *CurProduct)
{
	int balance_factor = diff(CurProduct);

	if (balance_factor > 1)
	{
		if (diff(CurProduct->left) > 0)
			CurProduct = LL_rotation(CurProduct);
		else
			CurProduct = LR_rotation(CurProduct);
	}
	else if (balance_factor < -1)
	{
		if (diff(CurProduct->right) > 0)
			CurProduct = RL_rotation(CurProduct);
		else
			CurProduct = RR_rotation(CurProduct);
	}
	return CurProduct;
}

/*
Sorted By name
*/
product *storehouse::NameSort_Insert(product *root, string _name, string _category, string _brand, float _price, int _number)
{
	if (root == NULL)
	{
		root = new product;
		root->name = _name;
		root->category = _category;
		root->brand = _brand;
		root->price = _price;
		root->number = _number;
		root->left = NULL;
		root->right = NULL;
		return root;
	}
	else if (_name < root->name)
	{
		root->left = NameSort_Insert(root->left, _name, _category, _brand, _price, _number);
		root = balance_product(root);
	}
	else if (_name > root->name)
	{
		root->right = NameSort_Insert(root->right, _name, _category, _brand, _price, _number);
		root = balance_product(root);
	}
	return root;
}

/*
Sorted By price
*/
product* storehouse::PriceSort_Insert(product *root, string _name, string _category, string _brand, float _price, int _number)
{
	if (root == NULL)
	{
		root = new product;
		root->name = _name;
		root->category = _category;
		root->brand = _brand;
		root->price = _price;
		root->number = _number;
		root->left = NULL;
		root->right = NULL;
		return root;
	}
	else if (_price < root->price)
	{
		root->left = PriceSort_Insert(root->left, _name, _category, _brand, _price, _number);
		root = balance_product(root);
	}
	else if (_price > root->price)
	{
		root->right = PriceSort_Insert(root->right, _name, _category, _brand, _price, _number);
		root = balance_product(root);
	}
	return root;
}

/*
Sorted By number
*/
product *storehouse::NumberSort_Insert(product *root, string _name, string _category, string _brand, float _price, int _number)
{
	if (root == NULL)
	{
		root = new product;
		root->name = _name;
		root->category = _category;
		root->brand = _brand;
		root->price = _price;
		root->number = _number;
		root->left = NULL;
		root->right = NULL;
		return root;
	}
	else if (_number < root->number)
	{
		root->left = NumberSort_Insert(root->left, _name, _category, _brand, _price, _number);
		root = balance_product(root);
	}
	else if (_number > root->number)
	{
		root->right = NumberSort_Insert(root->right, _name, _category, _brand, _price, _number);
		root = balance_product(root);
	}
	return root;
}

/*
Inorder Traversal of AVL Tree
*/
void storehouse::InorderPrint(product *tree)
{
	if (tree == NULL)
		return;

	InorderPrint(tree->left);

	cout << "Name: " << tree->name << endl;
	cout << "Category: " << tree->category << endl;
	cout << "Brand: " << tree->brand << endl;
	cout << "Price: " << tree->price << endl;
	cout << "Number: " << tree->number << endl;
	cout << "------------------------------------" << endl;

	InorderPrint(tree->right);
}

/*
NameSort Search
*/
product * storehouse::NameSort_Search(product *CurProduct, string temp)
{
	while (CurProduct)
	{
		if (temp == CurProduct->name)
			return CurProduct;
		else if (temp > CurProduct->name)
			CurProduct = CurProduct->right;
		else
			CurProduct = CurProduct->left;
	}
	return NULL;
}

/*
PriceSort Search
*/
product * storehouse::PriceSort_Search(product *CurProduct, int _temp)
{
	while (CurProduct)
	{
		if (_temp == CurProduct->price)
			return CurProduct;
		else if (_temp > CurProduct->price)
			CurProduct = CurProduct->right;
		else
			CurProduct = CurProduct->left;
	}
	return NULL;
}

/*
NumberSort Search
*/
product * storehouse::NumberSort_Search(product *CurProduct, int _temp)
{
	while (CurProduct)
	{
		if (_temp == CurProduct->number)
			return CurProduct;
		else if (_temp > CurProduct->number)
			CurProduct = CurProduct->right;
		else
			CurProduct = CurProduct->left;
	}
	return NULL;
}

/*
Print NameSort search result
*/
void storehouse::NameSort_SearchPrint(product *CurProduct, string temp)
{
	product *p = NameSort_Search(CurProduct, temp);

	if (p)
	{
		cout << "Name: " << p->name << endl;
		cout << "Category: " << p->category << endl;
		cout << "Brand: " << p->brand << endl;
		cout << "Price: " << p->price << endl;
		cout << "Number: " << p->number << endl;
	}
	else
		cout << "The product not found!" << endl;
}

/*
Print PriceSort search result
*/
void storehouse::PriceSort_SearchPrint(product *CurProduct, int _temp)
{
	product *p = PriceSort_Search(CurProduct, _temp);

	if (p)
	{
		cout << "Name: " << p->name << endl;
		cout << "Category: " << p->category << endl;
		cout << "Brand: " << p->brand << endl;
		cout << "Price: " << p->price << endl;
		cout << "Number: " << p->number << endl;
	}
	else
		cout << "The product not found!" << endl;
}

/*
Print NumberSort search result
*/
void storehouse::NumberSort_SearchPrint(product *CurProduct, int _temp)
{
	product *p = NumberSort_Search(CurProduct, _temp);

	if (p)
	{
		cout << "Name: " << p->name << endl;
		cout << "Category: " << p->category << endl;
		cout << "Brand: " << p->brand << endl;
		cout << "Price: " << p->price << endl;
		cout << "Number: " << p->number << endl;
	}
	else
		cout << "The product not found!" << endl;
}

/*
next inorder node
*/
product *storehouse::Successor(product *CurProduct)
{
	product *current = CurProduct;

	while (current->left != NULL)
		current = current->left;

	return current;
}

/*
NameSort Delete
*/
product* storehouse::NameSort_Delete(product *CurProduct, string temp)
{
	if (CurProduct == NULL) return CurProduct;

	if (temp < CurProduct->name)
		CurProduct->left = NameSort_Delete(CurProduct->left, temp);

	else if (temp > CurProduct->name)
		CurProduct->right = NameSort_Delete(CurProduct->right, temp);

	else
	{
		// node with only one child or no child
		if (CurProduct->left == NULL)
		{
			product *p = CurProduct->right;
			free(CurProduct);
			return p;
		}
		else if (CurProduct->right == NULL)
		{
			product *p = CurProduct->left;
			free(CurProduct);
			return p;
		}

		// node with two children: Get the inorder successor
		product *p = Successor(CurProduct->right);

		// Copy the inorder successor's content to this node
		CurProduct->name = p->name;
		CurProduct->category = p->category;
		CurProduct->brand = p->brand;
		CurProduct->price = p->price;
		CurProduct->name = p->number;

		// Delete the inorder successor
		CurProduct->right = NameSort_Delete(CurProduct->right, p->name);
	}
	return CurProduct;
}

/*
PriceSort Delete
*/
product* storehouse::PriceSort_Delete(product *CurProduct, int _temp)
{
	if (CurProduct == NULL) return CurProduct;

	if (_temp < CurProduct->price)
		CurProduct->left = PriceSort_Delete(CurProduct->left, _temp);

	else if (_temp > CurProduct->price)
		CurProduct->right = PriceSort_Delete(CurProduct->right, _temp);

	else
	{
		// node with only one child or no child
		if (CurProduct->left == NULL)
		{
			product *p = CurProduct->right;
			free(CurProduct);
			return p;
		}
		else if (CurProduct->right == NULL)
		{
			product *p = CurProduct->left;
			free(CurProduct);
			return p;
		}

		// node with two children: Get the inorder successor
		product *p = Successor(CurProduct->right);

		// Copy the inorder successor's content to this node
		CurProduct->name = p->name;
		CurProduct->category = p->category;
		CurProduct->brand = p->brand;
		CurProduct->price = p->price;
		CurProduct->name = p->number;

		// Delete the inorder successor
		CurProduct->right = PriceSort_Delete(CurProduct->right, p->price);
	}
	return CurProduct;
}

/*
NumberSort Delete
*/
product* storehouse::NumberSort_Delete(product *CurProduct, int _temp)
{
	if (CurProduct == NULL) return CurProduct;

	if (_temp < CurProduct->number)
		CurProduct->left = NumberSort_Delete(CurProduct->left, _temp);

	else if (_temp > CurProduct->number)
		CurProduct->right = NumberSort_Delete(CurProduct->right, _temp);

	else
	{
		// node with only one child or no child
		if (CurProduct->left == NULL)
		{
			product *p = CurProduct->right;
			free(CurProduct);
			return p;
		}
		else if (CurProduct->right == NULL)
		{
			product *p = CurProduct->left;
			free(CurProduct);
			return p;
		}

		// node with two children: Get the inorder successor
		product *p = Successor(CurProduct->right);

		// Copy the inorder successor's content to this node
		CurProduct->name = p->name;
		CurProduct->category = p->category;
		CurProduct->brand = p->brand;
		CurProduct->price = p->price;
		CurProduct->name = p->number;

		// Delete the inorder successor
		CurProduct->right = NumberSort_Delete(CurProduct->right, p->number);
	}
	return CurProduct;
}

//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------

struct account
{
	string name;
	int BuyNo;
	float BuyCost;
	int ProductCost;
	account *left, *right;
}*customer, *salesman;

account* storehouse::NameSort_Insert_account(account *root, string _name, int _BuyNo, float _BuyCost, int _ProductCost)
{
	if (root == NULL)
	{
		root = new account;
		root->name = _name;
		root->BuyNo = _BuyNo;
		root->BuyCost = _BuyCost;
		root->ProductCost = _ProductCost;
		root->left = NULL;
		root->right = NULL;
		return root;
	}
	else if (_name < root->name)
	{
		root->left = NameSort_Insert_account(root->left, _name, _BuyNo, _BuyCost, _ProductCost);
		root = balance(root);
	}
	else if (_name > root->name)
	{
		root->right = NameSort_Insert(root->right, _name, _BuyNo, _BuyCost, _ProductCost);
		root = balance(root);
	}
	return root;
}


/*
Main Menu
*/
void main()
{
	system("color 3b");

	// storehouse
	storehouse MyStorehouse;

	// product details
	string _name, _category, _brand;
	float _price;
	int _number;

	// string for search, update & delete
	string temp;
	// int for search, update & delete
	int _temp1, _temp2;

	// root of trees
	NameSortRoot = PriceSortRoot = NumberSortRoot = NULL;

	while (true)
	{
		cout << endl << endl << endl << endl;
		cout << "               *******************************************************************************************" << endl;
		cout << "               *                                                                                         *" << endl;
		cout << "               *                                    -=(Storehouse)=-                                     *" << endl;
		cout << "               *                                Please enter your option!                                *" << endl;
		cout << "               *                                                                                         *" << endl;
		cout << "               *                                                                                         *" << endl;
		cout << "               *  1) Insert a new product                                                                *" << endl;
		cout << "               *  2) Display products                                                                    *" << endl;
		cout << "               *  3) Search a product                                                                    *" << endl;
		cout << "               *  4) Update a product                                                                    *" << endl;
		cout << "               *  5) Delete a product                                                                    *" << endl;
		cout << "               *                                                                                         *" << endl;
		cout << "               *                                                                                         *" << endl;
		cout << "               *                                                                                         *" << endl;
		cout << "               *                                                                                         *" << endl;
		cout << "               *                                                                                         *" << endl;
		cout << "               *                                                                                         *" << endl;
		cout << "               *******************************************************************************************" << endl;

		switch (_getch())
		{
		case '1':
			system("cls");

			cout << "Insert a new product" << endl;
			cout << "Name: ";         cin >> _name;
			cout << "Category: ";     cin >> _category;
			cout << "Brand: ";        cin >> _brand;
			cout << "Price: ";        cin >> _price;
			cout << "Number: ";       cin >> _number;

			NameSortRoot = MyStorehouse.NameSort_Insert(NameSortRoot, _name, _category, _brand, _price, _number);
			PriceSortRoot = MyStorehouse.PriceSort_Insert(PriceSortRoot, _name, _category, _brand, _price, _number);
			NumberSortRoot = MyStorehouse.NumberSort_Insert(NameSortRoot, _name, _category, _brand, _price, _number);

			system("cls");
			break;

		case '2':
			system("cls");

			cout << "Display products" << endl;
			cout << "1) Sort by name" << endl;
			cout << "2) Sort by price" << endl;
			cout << "3) Sort by number" << endl;

			switch (_getch())
			{
			case '1':
				system("cls");
				cout << "Display products, Sort by name" << endl << endl;
				MyStorehouse.InorderPrint(NameSortRoot);
				break;

			case '2':
				system("cls");
				cout << "Display products, Sort by price" << endl << endl;
				MyStorehouse.InorderPrint(PriceSortRoot);
				break;

			case '3':
				system("cls");
				cout << "Display products, Sort by number" << endl << endl;
				MyStorehouse.InorderPrint(NumberSortRoot);
				break;

			default:
				system("cls");
				cout << "Sorry, you entered wrong character" << endl;
				break;
			}

			cout << "Press any key to continue ...";
			_getch();
			system("cls");
			break;

		case '3':
			system("cls");

			cout << "Search a product" << endl;
			cout << "1) Search by name" << endl;
			cout << "2) Search by price" << endl;
			cout << "3) Search by number" << endl;

			switch (_getch())
			{
			case '1':
				system("cls");

				cout << "Enter the name of product : ";
				cin >> temp;

				system("cls");
				MyStorehouse.NameSort_SearchPrint(NameSortRoot, temp);
				break;

			case '2':
				system("cls");

				cout << "Enter the price of product : ";
				cin >> _temp1;

				system("cls");
				MyStorehouse.PriceSort_SearchPrint(NameSortRoot, _temp1);
				break;

			case '3':
				system("cls");

				cout << "Enter the number of product : ";
				cin >> _temp2;

				system("cls");
				MyStorehouse.NumberSort_SearchPrint(NameSortRoot, _temp2);
				break;

			default:
				system("cls");
				cout << "Sorry, you entered wrong character" << endl;
				break;
			}

			cout << "Press any key to continue ...";
			_getch();
			system("cls");
			break;

		case '4':
			system("cls");

			cout << "Update a product" << endl;
			cout << "Enter the name of product : ";     cin >> temp;
			cout << "Enter the price of product : ";     cin >> _temp1;
			cout << "Enter the number of product : ";     cin >> _temp2;

			system("cls");

			cout << "Insert a new product" << endl;
			cout << "Name: ";         cin >> _name;
			cout << "Category: ";     cin >> _category;
			cout << "Brand: ";        cin >> _brand;
			cout << "Price: ";        cin >> _price;
			cout << "Number: ";       cin >> _number;

			system("cls");

			NameSortRoot = MyStorehouse.NameSort_Delete(NameSortRoot, temp);
			NameSortRoot = MyStorehouse.NameSort_Insert(NameSortRoot, _name, _category, _brand, _price, _number);

			PriceSortRoot = MyStorehouse.PriceSort_Delete(PriceSortRoot, _temp1);
			PriceSortRoot = MyStorehouse.PriceSort_Insert(PriceSortRoot, _name, _category, _brand, _price, _number);

			NumberSortRoot = MyStorehouse.NumberSort_Delete(NumberSortRoot, _temp2);
			NumberSortRoot = MyStorehouse.NumberSort_Insert(NumberSortRoot, _name, _category, _brand, _price, _number);

			cout << "Updated successfuly!" << endl;
			cout << "Press any key to continue ...";
			_getch();
			system("cls");
			break;

		case '5':
			system("cls");

			cout << "Delete a product" << endl;
			cout << "Enter the name of product : ";     cin >> temp;
			cout << "Enter the price of product : ";     cin >> _temp1;
			cout << "Enter the number of product : ";     cin >> _temp2;

			system("cls");
			NameSortRoot = MyStorehouse.NameSort_Delete(NameSortRoot, temp);
			PriceSortRoot = MyStorehouse.PriceSort_Delete(PriceSortRoot, _temp1);
			NumberSortRoot = MyStorehouse.NumberSort_Delete(NumberSortRoot, _temp2);

			cout << "Deleted successfuly!" << endl;
			cout << "Press any key to continue ...";
			_getch();
			system("cls");
			break;

		default:
			system("cls");
			cout << "Sorry, you entered wrong character" << endl;
			cout << "Press any key to continue ...";
			_getch();
			system("cls");
		}
	}
}