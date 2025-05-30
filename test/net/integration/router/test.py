#!/usr/bin/env python3

from __future__ import print_function
from future import standard_library
standard_library.install_aliases()
from builtins import str
import sys
import os
import subprocess
import _thread
import time

thread_timeout = 60

from vmrunner import vmrunner

iperf_cmd = "iperf3"
transmit_size = "100M"

nsname="server1"

def move_tap1(o):
    subprocess.call(["./setup.sh", "--vmsetup"])

def clean():
    subprocess.call(["sudo","pkill",iperf_cmd])
    subprocess.call(["./setup.sh", "--clean"])


def iperf_server():
    subprocess.Popen(["sudo","ip","netns","exec", nsname, iperf_cmd, "-s"],
                                    stdout = subprocess.PIPE,
                                    stdin = subprocess.PIPE,
                                    stderr = subprocess.PIPE)

def iperf_client(o):
    print("Starting iperf client. Iperf output: ")
    print(subprocess.check_output([iperf_cmd,"-c","10.42.42.2","-n", transmit_size], timeout=thread_timeout))
    vmrunner.vms[0].exit(0, "Test completed without errors")
    return True

#clean anything hangig after a crash.. from previous test
subprocess.call(["./setup.sh", "--clean"])
subprocess.call("./setup.sh")

vm = vmrunner.vms[0]

# Move second interface to second bridge, right after boot
vm.on_output("Routing test", move_tap1)

# Start iperf server right away, client when vm is up
_thread.start_new_thread(iperf_server, ())
vm.on_output("Service ready", iperf_client)

# Clean
vm.on_exit(clean)

if len(sys.argv) > 1:
    vm.boot(image_name=str(sys.argv[1]))
else:
    # Boot the VM, taking a timeout as parameter
    vm.boot(thread_timeout,image_name='net_router.elf.bin')
