from plumbum.cmd import history
cmd = (history)()
history_feq = dict()
for line in cmd.split('\n'):
    if line != "":
        command = line.split()[1]
        command = command.replace("./", '')
        if command in history_freq.keys():
            history_freq[command] = history_freq[command]+1
        else:
            history_freq[command]=1
for command in history_freq.keys():
    print command,history_freq[command]
