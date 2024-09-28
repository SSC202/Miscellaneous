#include <iostream>

using namespace std;

int main()
{
    // 标准输出流
    char str[] = "Hello C++";

    cout << "Value of str is : " << str << endl;

    system("pause");

    // 标准输入流
    char name[50];

    cout << "请输入您的名称： ";
    cin >> name;
    cout << "您的名称是： " << name << endl;

    system("pause");

    // 标准错误流
    char err_str[] = "Unable to read....";

    cerr << "Error message : " << err_str << endl;

    system("pause");

    // 标准日志流
    char log_str[] = "Unable to read....";

    clog << "Error message : " << log_str << endl;

    system("pause");
}