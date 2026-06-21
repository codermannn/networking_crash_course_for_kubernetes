import sys
import re

def parse_tcpdump_line(line):
    # Matches lines like: 12:00:00.123 IP 172.20.0.2.12345 > 172.20.0.3.80: Flags [P.], seq 1001:1021, ack 1, win 502, length 20
    # Or: Flags [.], ack 1021, win 502, length 0
    
    time_match = re.search(r'^(\d+:\d+:\d+\.\d+)', line)
    if not time_match:
        return None
    
    timestamp = time_match.group(1)
    
    # Extract flags
    flags_match = re.search(r'Flags \[(.*?)\]', line)
    flags = flags_match.group(1) if flags_match else ""
    
    # Extract seq
    seq_match = re.search(r'seq (\d+)(:\d+)?', line)
    seq = seq_match.group(1) if seq_match else ""
    
    # Extract ack
    ack_match = re.search(r'ack (\d+)', line)
    ack = ack_match.group(1) if ack_match else ""
    
    length_match = re.search(r'length (\d+)', line)
    length = length_match.group(1) if length_match else "0"
    
    return {
        "time": timestamp,
        "flags": flags,
        "seq": seq,
        "ack": ack,
        "len": length
    }

print(f"{'Timestamp':<15} | {'Flags':<5} | {'Seq Number':<12} | {'Ack Number':<12} | {'Length':<5}")
print("-" * 60)

for line in sys.stdin:
    parsed = parse_tcpdump_line(line.strip())
    if parsed:
        # Only print TCP packets that have seq, ack, or handshake flags
        if parsed["seq"] or parsed["ack"] or 'S' in parsed["flags"] or 'F' in parsed["flags"]:
            print(f"{parsed['time']:<15} | {parsed['flags']:<5} | {parsed['seq']:<12} | {parsed['ack']:<12} | {parsed['len']:<5}")
