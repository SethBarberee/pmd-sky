from dataclasses import dataclass

MIXED_CASE_SYMBOLS = {
    '_secure': 'SECURE',
    '_start_AutoloadDoneCallback': 'StartAutoloadDoneCallback',
    '_start_ModuleParams': 'START_MODULE_PARAMS',
    'MIi_UncompressBackward': 'MIiUncompressBackward',
    'OSi_ReferSymbol': 'OSiReferSymbol',
    'SVC_CpuSet': 'SvcCpuSet',
    'SVC_SoftReset': 'SvcSoftReset',
    'SVC_WaitByLoop': 'SvcWaitByLoop',
    'SVC_WaitByLoop': 'SvcWaitByLoop',
}

@dataclass
class SymbolDetails:
    name: str
    file_path: str
    is_data: bool
