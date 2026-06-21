import sys
import os

def parse_conntrack_file(filepath):
    if not os.path.exists(filepath):
        print(f"Error: {filepath} not found. Is connection tracking module loaded?")
        return
    
    print(f"{'Proto':<6} | {'Original (Src -> Dst)':<35} | {'Reply (Src -> Dst)':<35} | {'State':<12}")
    print("-" * 96)
    
    with open(filepath, 'r') as f:
        for line in f:
            parts = line.strip().split()
            if len(parts) < 4:
                continue
            
            proto = parts[2]
            state = ""
            
            # Find state if it's TCP
            for p in parts:
                if p in ["ESTABLISHED", "TIME_WAIT", "SYN_SENT", "SYN_RECV", "CLOSE"]:
                    state = p
                    break
            
            # Find src/dst key-values
            kvs = []
            for p in parts:
                if '=' in p:
                    kvs.append(p)
            
            if len(kvs) >= 8:
                orig_src = kvs[0]
                orig_dst = kvs[1]
                orig_sport = kvs[2]
                orig_dport = kvs[3]
                
                reply_src = kvs[4]
                reply_dst = kvs[5]
                reply_sport = kvs[6]
                reply_dport = kvs[7]
                
                orig_str = f"{orig_src.split('=')[1]}:{orig_sport.split('=')[1]} -> {orig_dst.split('=')[1]}:{orig_dport.split('=')[1]}"
                reply_str = f"{reply_src.split('=')[1]}:{reply_sport.split('=')[1]} -> {reply_dst.split('=')[1]}:{reply_dport.split('=')[1]}"
                
                print(f"{proto:<6} | {orig_str:<35} | {reply_str:<35} | {state:<12}")

if __name__ == "__main__":
    path = "/proc/net/nf_conntrack"
    if len(sys.argv) > 1:
        path = sys.argv[1]
    parse_conntrack_file(path)
