#include "LoginService.h"
#include "mysqldb.h"

int main(int argc, char **argv)
{
    MprpcApplication::Init(argc, argv);

    connection_pool::GetInstance()->init();

    RpcProvider provider;
    provider.NotifyService(new LoginService());

    provider.Run();

    return 0;
}