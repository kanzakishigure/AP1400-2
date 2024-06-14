#pragma once
#include <string>
#include <memory>
#include <map>
#include <vector>

class Client;
class Server
{

	friend void  show_wallets(const  Server& server);
public:
	Server();
	std::shared_ptr<Client> add_client(std::string id);
	const std::shared_ptr<Client> get_client(std::string id)const;
	
	const double get_wallet(std::string id)const;
	
	const bool add_pending_trx(std::string trx, std::string signature)const;
	std::size_t mine();

	static bool parse_trx(const std::string& trx, std::string& sender, std::string& receiver, double& value);
private:
	const std::vector<std::string> split_trx(std::string trx)const;
	const double parse_trx_money(std::string trxMoney)const;
	std::map<std::shared_ptr<Client>, double> clients;
};


