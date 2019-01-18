
import re
re_Bjet = re.compile(r'^HLT_(?P<multiplicity>\d+)?j(?P<threshold>\d+)(?:_gsc(?P<gscThreshold>\d+))?(?:_b(?P<bTag>[^_]+)(?:_(?P<bConfig>split))?(?:_(?P<minEta>\d+)eta(?P<maxEta>\d+))?)?(?:_L1(?P<L1>.*))?$')

default_conf = { 'threshold' : '0',
                 'multiplicity' : '1',
                 'gscThreshold' : '0',
                 'bTag' : 'offperf',
                 'bConfig' : 'EF',
                 'minEta' : '0',
                 'maxEta' : '320',
                 'L1' : None }

triggerName = [
    "HLT_j35_boffperf",
    "HLT_j35_boffperf_split",
    "HLT_j35_gsc45_boffperf",
    "HLT_j35_gsc45_boffperf_split",
    "HLT_j35_boffperf_230eta490",
    "HLT_j35_boffperf_split_230eta490",
    "HLT_j35_gsc45_boffperf_230eta490",
    "HLT_j35_gsc45_boffperf_split_230eta490",
    "HLT_3j35_boffperf",
    "HLT_3j35_boffperf_split",
    "HLT_3j35_gsc45_boffperf",
    "HLT_3j35_gsc45_boffperf_split",
    "HLT_3j35_boffperf_230eta490",
    "HLT_3j35_boffperf_split_230eta490",
    "HLT_3j35_gsc45_boffperf_230eta490",
    "HLT_3j35_gsc45_boffperf_split_230eta490",
    "HLT_j35_boffperf_L1J15",
    "HLT_j35_boffperf_split_L1J15",
    "HLT_j35_gsc45_boffperf_L1J15",
    "HLT_j35_gsc45_boffperf_split_L1J15",
    "HLT_j35_boffperf_230eta490_L1J15",
    "HLT_j35_boffperf_split_230eta490_L1J15",
    "HLT_j35_gsc45_boffperf_230eta490_L1J15",
    "HLT_j35_gsc45_boffperf_split_230eta490_L1J15",
    "HLT_3j35_boffperf_L1J15",
    "HLT_3j35_boffperf_split_L1J15",
    "HLT_3j35_gsc45_boffperf_L1J15",
    "HLT_3j35_gsc45_boffperf_split_L1J15",
    "HLT_3j35_boffperf_230eta490_L1J15",
    "HLT_3j35_boffperf_split_230eta490_L1J15",
    "HLT_3j35_gsc45_boffperf_230eta490_L1J15",
    "HLT_3j35_gsc45_boffperf_split_230eta490_L1J15",
    ]

referenceConfiguration = [
    {'bTag': 'offperf', 'bConfig': 'EF', 'maxEta': '320', 'multiplicity': '1', 'minEta': '0', 'gscThreshold': '0', 'L1': None, 'threshold': '35'},
    {'bTag': 'offperf', 'bConfig': 'split', 'maxEta': '320', 'multiplicity': '1', 'minEta': '0', 'gscThreshold': '0', 'L1': None, 'threshold': '35'},
    {'bTag': 'offperf', 'bConfig': 'EF', 'maxEta': '320', 'multiplicity': '1', 'minEta': '0', 'gscThreshold': '45', 'L1': None, 'threshold': '35'},
    {'bTag': 'offperf', 'bConfig': 'split', 'maxEta': '320', 'multiplicity': '1', 'minEta': '0', 'gscThreshold': '45', 'L1': None, 'threshold': '35'},
    {'bTag': 'offperf', 'bConfig': 'EF', 'maxEta': '490', 'multiplicity': '1', 'minEta': '230', 'gscThreshold': '0', 'L1': None, 'threshold': '35'},
    {'bTag': 'offperf', 'bConfig': 'split', 'maxEta': '490', 'multiplicity': '1', 'minEta': '230', 'gscThreshold': '0', 'L1': None, 'threshold': '35'},
    {'bTag': 'offperf', 'bConfig': 'EF', 'maxEta': '490', 'multiplicity': '1', 'minEta': '230', 'gscThreshold': '45', 'L1': None, 'threshold': '35'},
    {'bTag': 'offperf', 'bConfig': 'split', 'maxEta': '490', 'multiplicity': '1', 'minEta': '230', 'gscThreshold': '45', 'L1': None, 'threshold': '35'},
    {'bTag': 'offperf', 'bConfig': 'EF', 'maxEta': '320', 'multiplicity': '3', 'minEta': '0', 'gscThreshold': '0', 'L1': None, 'threshold': '35'},
    {'bTag': 'offperf', 'bConfig': 'split', 'maxEta': '320', 'multiplicity': '3', 'minEta': '0', 'gscThreshold': '0', 'L1': None, 'threshold': '35'},
    {'bTag': 'offperf', 'bConfig': 'EF', 'maxEta': '320', 'multiplicity': '3', 'minEta': '0', 'gscThreshold': '45', 'L1': None, 'threshold': '35'},
    {'bTag': 'offperf', 'bConfig': 'split', 'maxEta': '320', 'multiplicity': '3', 'minEta': '0', 'gscThreshold': '45', 'L1': None, 'threshold': '35'},
    {'bTag': 'offperf', 'bConfig': 'EF', 'maxEta': '490', 'multiplicity': '3', 'minEta': '230', 'gscThreshold': '0', 'L1': None, 'threshold': '35'},
    {'bTag': 'offperf', 'bConfig': 'split', 'maxEta': '490', 'multiplicity': '3', 'minEta': '230', 'gscThreshold': '0', 'L1': None, 'threshold': '35'},
    {'bTag': 'offperf', 'bConfig': 'EF', 'maxEta': '490', 'multiplicity': '3', 'minEta': '230', 'gscThreshold': '45', 'L1': None, 'threshold': '35'},
    {'bTag': 'offperf', 'bConfig': 'split', 'maxEta': '490', 'multiplicity': '3', 'minEta': '230', 'gscThreshold': '45', 'L1': None, 'threshold': '35'},
    {'bTag': 'offperf', 'bConfig': 'EF', 'maxEta': '320', 'multiplicity': '1', 'minEta': '0', 'gscThreshold': '0', 'L1': 'J15', 'threshold': '35'},
    {'bTag': 'offperf', 'bConfig': 'split', 'maxEta': '320', 'multiplicity': '1', 'minEta': '0', 'gscThreshold': '0', 'L1': 'J15', 'threshold': '35'},
    {'bTag': 'offperf', 'bConfig': 'EF', 'maxEta': '320', 'multiplicity': '1', 'minEta': '0', 'gscThreshold': '45', 'L1': 'J15', 'threshold': '35'},
    {'bTag': 'offperf', 'bConfig': 'split', 'maxEta': '320', 'multiplicity': '1', 'minEta': '0', 'gscThreshold': '45', 'L1': 'J15', 'threshold': '35'},
    {'bTag': 'offperf', 'bConfig': 'EF', 'maxEta': '490', 'multiplicity': '1', 'minEta': '230', 'gscThreshold': '0', 'L1': 'J15', 'threshold': '35'},
    {'bTag': 'offperf', 'bConfig': 'split', 'maxEta': '490', 'multiplicity': '1', 'minEta': '230', 'gscThreshold': '0', 'L1': 'J15', 'threshold': '35'},
    {'bTag': 'offperf', 'bConfig': 'EF', 'maxEta': '490', 'multiplicity': '1', 'minEta': '230', 'gscThreshold': '45', 'L1': 'J15', 'threshold': '35'},
    {'bTag': 'offperf', 'bConfig': 'split', 'maxEta': '490', 'multiplicity': '1', 'minEta': '230', 'gscThreshold': '45', 'L1': 'J15', 'threshold': '35'},
    {'bTag': 'offperf', 'bConfig': 'EF', 'maxEta': '320', 'multiplicity': '3', 'minEta': '0', 'gscThreshold': '0', 'L1': 'J15', 'threshold': '35'},
    {'bTag': 'offperf', 'bConfig': 'split', 'maxEta': '320', 'multiplicity': '3', 'minEta': '0', 'gscThreshold': '0', 'L1': 'J15', 'threshold': '35'},
    {'bTag': 'offperf', 'bConfig': 'EF', 'maxEta': '320', 'multiplicity': '3', 'minEta': '0', 'gscThreshold': '45', 'L1': 'J15', 'threshold': '35'},
    {'bTag': 'offperf', 'bConfig': 'split', 'maxEta': '320', 'multiplicity': '3', 'minEta': '0', 'gscThreshold': '45', 'L1': 'J15', 'threshold': '35'},
    {'bTag': 'offperf', 'bConfig': 'EF', 'maxEta': '490', 'multiplicity': '3', 'minEta': '230', 'gscThreshold': '0', 'L1': 'J15', 'threshold': '35'},
    {'bTag': 'offperf', 'bConfig': 'split', 'maxEta': '490', 'multiplicity': '3', 'minEta': '230', 'gscThreshold': '0', 'L1': 'J15', 'threshold': '35'},
    {'bTag': 'offperf', 'bConfig': 'EF', 'maxEta': '490', 'multiplicity': '3', 'minEta': '230', 'gscThreshold': '45', 'L1': 'J15', 'threshold': '35'},
    {'bTag': 'offperf', 'bConfig': 'split', 'maxEta': '490', 'multiplicity': '3', 'minEta': '230', 'gscThreshold': '45', 'L1': 'J15', 'threshold': '35'},
    ]

def compareConfigurationWithReference( index, conf_dict ):
    referenceConfig = referenceConfiguration[index]
    if len( referenceConfig ) != len( conf_dict ): return False
    for (key,value) in referenceConfig.items():
        if conf_dict[ key ] != referenceConfig[ key ]: return False
    return True

for index in range(0,len(triggerName)):
    chain = triggerName[index]
    print 'Parsing chain :',chain
    match = re_Bjet.match( chain )
    conf_dict = match.groupdict()
    
    for k, v in default_conf.items():
        if k not in conf_dict: conf_dict[k] = v
        if conf_dict[k] == None: conf_dict[k] = v

    print 'Inferred :',conf_dict
    print 'Reference:', referenceConfiguration[index]
    if compareConfigurationWithReference( index, conf_dict ) == False:
        print 'ERROR IN TRIGGER NAME PARSING'
    else:
        print "CORRECT CONFIGURATION"
    print ""




