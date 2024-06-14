#include "client.h"
#include "server.h"
#include <cstddef>
#include <ostream>
#include <sstream>
#include <string>
#include <crypto.h>
#include <string>
#include <random>
#include <chrono>



Client::Client(std::string id, const Server &server)
:server(&server),id(id)
{
   crypto::generate_key(public_key,private_key);
}

std::string Client::get_id()
{
    return id;
}

const std::string Client::get_publickey() const
{
    return public_key;
}

double Client::get_wallet() 
{
    return server->get_wallet(id);
}


const std::string Client::sign(std::string txt)const
{
    std::string signature = crypto::signMessage(private_key, txt);;
    
    return signature;
}

bool Client::transfer_money(std::string receiver, double value)
{
    
    std::string trx_str ;
    std::stringstream ss;
    ss<< id <<'-' <<receiver <<'-'<< value;
    trx_str = ss.str();

    std::cout<<trx_str<<std::endl;
    std::string signature = sign(trx_str);
    
    return  server->add_pending_trx(trx_str, signature);
}

std::size_t Client::generate_nonce()
{
    unsigned long ticks = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 urbg {ticks}; 
    std::uniform_int_distribution<size_t> uniformDistribution;
    
    return uniformDistribution(urbg);
}
