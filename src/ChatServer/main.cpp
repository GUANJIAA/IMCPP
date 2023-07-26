#include "ChatService.h"
#include "mprpcapplication.h"
#include "rpcprovider.h"

#include "mysqldb.h"

int main(int argc, char **argv)
{
    MprpcApplication::Init(argc, argv);

    connection_pool::GetInstance()->init();

    RpcProvider provider;
    provider.NotifyService(new ChatService());

    provider.Run();

    return 0;
}