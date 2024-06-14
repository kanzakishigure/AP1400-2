#include "server.h"
#include "client.h"

#include <cmath>
#include <cstddef>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <crypto.h>
#include <random>
#include <chrono>

std::vector<std::string> pending_trxs;

Server::Server()
{
}

std::shared_ptr<Client> Server::add_client(std::string id)
{
   if(get_client(id)!=nullptr)
   {
        unsigned long ticks = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 urbg {ticks}; 
        std::uniform_int_distribution<size_t> uniformDistribution;
        std::stringstream ss ;
        ss<< id<<uniformDistribution(urbg);
        id = ss.str();
   }
    std::shared_ptr<Client> client = std::make_shared<Client>(id,*this);
    clients[client] = 5.0;

    return client;
}

const std::shared_ptr<Client> Server::get_client(std::string id)const 
{

     for(auto client : clients)
    {
        if(client.first->get_id()==id)
        {
            return client.first;
        }
    }
    return nullptr;
}



const double Server::get_wallet(std::string id) const
{
    for(auto client : clients)
    {
        if(client.first->get_id()==id)
        {
            return client.second;
        }
    }
    return 0.0;
}

bool Server::parse_trx(const std::string& trx, std::string& sender, std::string& receiver, double& value)
{
    std::vector<std::string> trxStr = {};
    std::string itStr = trx;
    size_t it = 0;
    while(it!=itStr.npos)
    {
        it = itStr.find_first_of('-');
        
        if(it!=itStr.npos)
        {
            trxStr.push_back(itStr.substr(0,it));
            itStr = itStr.substr(it+1,itStr.size()-it-1);
        }
        else
        {
            trxStr.push_back(itStr);
        }
        
        
    }
    
    
    if(trxStr.size()!=3)
    {
        throw  std::runtime_error("invalid trx");
    }
    
    it = trxStr[2].find_first_of('.');
    double initialValue =1;
    if(it!=std::string::npos)
    {
        initialValue = initialValue/((trxStr[2].size()-it-1)*10);
    }
    double currency = 0;
    for(int i=trxStr[2].size()-1;i>=0;i--)
    {
        if(trxStr[2][i]!='.')
        {
            currency += initialValue*(trxStr[2][i] - '0');
            initialValue = initialValue*10;
        }
        
    }
    sender = trxStr[0];
    receiver = trxStr[1];
    value = currency;
    return true;
}

const bool Server::add_pending_trx(std::string trx, std::string signature) const
{
    
    std::string sender = {};
    std::string receiver ={};
    double money = 0.0f;
    //check trx
    if(!Server::parse_trx(trx, sender, receiver, money))
    {
        return false;
    }
    //check sender and receiver
    if(get_client(sender)==nullptr||get_client(receiver)==nullptr)
    {
        return false;
    }
    // check signature
    if(!crypto::verifySignature(get_client(sender)->get_publickey(),trx , signature))
    {
        return  false;
    }
    // check the wallet
    if(get_wallet(sender)<money)
    {
        return  false;
    }
    pending_trxs.push_back(trx);
    return true;
}

std::size_t Server::mine()
{
    std::string mempool;
    for(auto trx:pending_trxs)
    {
        mempool+=trx;
    }
    while (true) {
    for(auto& client : clients)
    {
        std::size_t nonce = client.first->generate_nonce();
        std::string hash = crypto::sha256(mempool + std::to_string(nonce));
        if(hash.substr(0, 10).find("000000") != std::string::npos)
        {
            std::cout<<client.first->get_id()<<"Obtain rewards"<<std::endl;
            std::cout<< hash<<std::endl;
            //miner get rewards
            client.second+=6.25;

            for(auto trx:pending_trxs)
            {
                std::string sender;
                std::string receiver;
                double value = 0;
                Server::parse_trx(trx,sender,receiver,value);
                clients[get_client(sender)]-=value;
                clients[get_client(receiver)]+=value;
            }
            pending_trxs.clear();
            return nonce;
        }
    }
    }
    return std::size_t();
}

 const std::vector<std::string> Server::split_trx(std::string trx) const
{
    std::vector<std::string> trxStr = {};

    size_t it = 0;
    while(it!=trx.npos)
    {
        it = trx.find_first_of('-');
        
        if(it!=trx.npos)
        {
            trxStr.push_back(trx.substr(0,it));
            trx = trx.substr(it+1,trx.size()-it-1);
        }
        else
        {
            trxStr.push_back(trx);
        }
        
        
    }
    return  trxStr;
}
const double Server::parse_trx_money(std::string trxMoney)const
{
    double initialValue =1;
    size_t it = trxMoney.find_first_of('.');
    if(it!=std::string::npos)
    {
        initialValue = initialValue/((trxMoney.size()-it-1)*10);
    }
    double currency = 0;
    for(int i=trxMoney.size()-1;i>=0;i--)
    {
        if(trxMoney[i]!='.')
        {
            currency += initialValue*(trxMoney[i] - '0');
            initialValue = initialValue*10;
        }
        
    }
    return currency;
}

