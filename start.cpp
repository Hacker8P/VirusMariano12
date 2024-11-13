#include <Windows.h>
#include <Taskschd.h>
#include <Comdef.h>
#include <iostream>

#pragma comment(lib, "taskschd.lib")
#pragma comment(lib, "comsuppw.lib")

void CreateTaskScheduler() {
    HRESULT hr = S_OK;

    // Inizializzazione COM
    hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (FAILED(hr)) {
        std::cerr << "COM initialization failed!" << std::endl;
        return;
    }

    // Crea il servizio di Task Scheduler
    ITaskService* pService = NULL;
    hr = CoCreateInstance(CLSID_TaskScheduler, NULL, CLSCTX_INPROC_SERVER, IID_ITaskService, (void**)&pService);
    if (FAILED(hr)) {
        std::cerr << "Failed to create Task Scheduler Service" << std::endl;
        CoUninitialize();
        return;
    }

    // Connetti al Task Scheduler
    hr = pService->Connect(_variant_t(), _variant_t(), _variant_t(), _variant_t());
    if (FAILED(hr)) {
        std::cerr << "Could not connect to Task Scheduler" << std::endl;
        pService->Release();
        CoUninitialize();
        return;
    }

    // Crea una nuova attività
    ITaskDefinition* pTask = NULL;
    hr = pService->NewTask(0, &pTask);
    if (FAILED(hr)) {
        std::cerr << "Failed to create new task" << std::endl;
        pService->Release();
        CoUninitialize();
        return;
    }

    // Imposta l'informazione di registrazione
    IRegistrationInfo* pRegInfo = NULL;
    hr = pTask->get_RegistrationInfo(&pRegInfo);
    pRegInfo->put_Author(L"Your Name");

    // Impostazione dei trigger: la nostra attività si attiva all'avvio
    ITriggerCollection* pTriggers = NULL;
    hr = pTask->get_Triggers(&pTriggers);
    ITrigger* pTrigger = NULL;
    hr = pTriggers->Create(TASK_TRIGGER_BOOT, &pTrigger); // Esegui al boot
    IBootTrigger* pBootTrigger = NULL;
    hr = pTrigger->QueryInterface(IID_IBootTrigger, (void**)&pBootTrigger);

    // Impostazione dell'azione: eseguire un programma
    IActionCollection* pActions = NULL;
    hr = pTask->get_Actions(&pActions);
    IAction* pAction = NULL;
    hr = pActions->Create(TASK_ACTION_EXEC, &pAction);
    IExecAction* pExecAction = NULL;
    hr = pAction->QueryInterface(IID_IExecAction, (void**)&pExecAction);

    // Impostiamo il percorso del programma da eseguire
    pExecAction->put_Path(L"%windir%\\winnt64.exe");

    // Impostazione delle opzioni di sicurezza: eseguire con privilegi elevati
    ITaskSettings* pSettings = NULL;
    hr = pTask->get_Settings(&pSettings);
    pSettings->put_AllowDemandStart(VARIANT_TRUE);   // Permetti l'avvio manuale
    pSettings->put_ExecutionTimeLimit(_bstr_t(L"PT0S")); // Nessun limite di tempo
    pSettings->put_DisallowStartIfOnBatteries(_variant_t(VARIANT_FALSE)); // Non impedire l'esecuzione su batteria
    pSettings->put_StartWhenAvailable(VARIANT_TRUE);  // Avvia l'attività quando il computer è disponibile

    // Ottieni la cartella di root
    ITaskFolder* pRootFolder = NULL;
    hr = pService->GetFolder(_bstr_t("\\"), &pRootFolder);
    if (FAILED(hr)) {
        std::cerr << "Failed to get root folder" << std::endl;
        pService->Release();
        CoUninitialize();
        return;
    }

    // Registra l'attività
    hr = pRootFolder->RegisterTaskDefinition(
        _bstr_t("MyTask - Esegui Programma con Privilegi"),
        pTask,
        TASK_CREATE_OR_UPDATE,
        _variant_t(L"Administrator"),      // Usa un account con privilegi di amministratore
        _variant_t(L""),                   // Se hai una password, mettila qui
        TASK_LOGON_INTERACTIVE_TOKEN,      // Usa il token interattivo
        _variant_t(L""),                   // Argomenti del programma
        NULL
    );

    if (FAILED(hr)) {
        std::cerr << "Failed to register the task" << std::endl;
    } else {
        std::cout << "Task registered successfully" << std::endl;
    }

    // Rilascia le risorse
    pService->Release();
    CoUninitialize();
}

int main() {
    CreateTaskScheduler();
    return 0;
}
