#include <orx.h>
#include <orxpm/orxpm.h>


orxSTATUS orxFASTCALL Init()
{
  orxPM_Init();

  return orxSTATUS_SUCCESS;
}


orxSTATUS orxFASTCALL Run()
{
  orxPM_Run();

  return orxSTATUS_SUCCESS;
}


void orxFASTCALL Exit()
{
  orxPM_Exit();
}


orxSTATUS orxFASTCALL Bootstrap ()
{
  orxPM_Bootstrap();

  return orxSTATUS_SUCCESS;
}


int main(int argc, char **argv)
{
  orxConfig_SetBootstrap(Bootstrap); 

  orx_Execute(argc, argv, Init, Run, Exit);

  return EXIT_SUCCESS;
}


#ifdef __orxMSVC__

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  orxConfig_SetBootstrap(Bootstrap); 

  orx_WinExecute(Init, Run, Exit);

  return EXIT_SUCCESS;
}

#endif // __orxMSVC__
