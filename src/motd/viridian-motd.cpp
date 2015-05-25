#include <iostream>
#include <unistd.h>
#include <boost/asio.hpp>
#include "uptime.h"

using namespace std;

int main()
{
	char* user = getlogin();
	string* hostname = new string();
	*hostname = boost::asio::ip::host_name();

	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);

	istringstream logo("__     ___      _     _ _             \n\\ \\   / (_)_ __(_) __| (_) __ _ _ __  \n \\ \\ / /| | '__| |/ _` | |/ _` | '_ \\ \n  \\ V / | | |  | | (_| | | (_| | | | |\n   \\_/  |_|_|  |_|\\__,_|_|\\__,_|_| |_|\n");

	string line;
	while(getline(logo, line))
	{
		int offset = (size.ws_col - 38) / 2;
		for(int i = 0; i < offset; i++)
			cout << " ";
		cout << line << endl;
	}
	size_t domainPos = hostname->find(".");
	string hostNameWithoutDomain = hostname->substr(0, domainPos);
	cout << "Logged in as " << user << " on " << hostNameWithoutDomain << "." << endl;

	unsigned int uptime = Uptime::get_uptime();

	int uptimeDays = uptime / 86400;
	uptime = uptime % 86400;
	int uptimeHours = uptime / 3600;
	uptime = uptime % 3600;
	int uptimeMinutes = uptime / 60;
	uptime = uptime % 60;

	if(uptimeDays > 0)
		cout << "System has been up for " << uptimeDays << " days, " << uptimeHours << " hours, " << uptimeMinutes << " minutes, and " << uptime << " seconds." << endl;
	else if(uptimeHours > 0)
		cout << "System has been up for " << uptimeHours << " hours, " << uptimeMinutes << " minutes, and " << uptime << " seconds." << endl;
	else if(uptimeMinutes > 0)
		cout << "System has been up for " << uptimeMinutes << " minutes " << uptime << " seconds." << endl;
	else
		cout << "System has been up for " << uptime << " seconds." << endl;


	delete hostname;

	return 0;
}
