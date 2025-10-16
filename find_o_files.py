#!/usr/bin/env python3
"""
Script to find all lines in config/G4QE01/splits.txt that end with *.o:

Usage:
    python3 find_o_files.py [options]

Options:
    --output FILE    Save results to a file
    --filter TEXT    Filter results by text pattern
    --count-only     Only show the count of matches
    --help           Show this help message
"""

import os
import sys
import argparse

def find_o_files(output_file=None, filter_text=None, count_only=False):
    """Find all lines ending with .o: in the splits.txt file"""
    splits_file = "config/G4QE01/splits.txt"
    
    if not os.path.exists(splits_file):
        print(f"Error: {splits_file} not found!")
        return
    
    o_files = []
    
    try:
        with open(splits_file, 'r', encoding='utf-8') as f:
            for line_num, line in enumerate(f, 1):
                line = line.rstrip('\n\r')
                if line.endswith('.o:'):
                    # Apply filter if specified
                    if filter_text is None or filter_text.lower() in line.lower():
                        o_files.append((line_num, line))
        
        if count_only:
            print(f"Found {len(o_files)} lines ending with .o:")
            return
        
        if o_files:
            output_lines = []
            output_lines.append(f"Found {len(o_files)} lines ending with .o:")
            output_lines.append("-" * 50)
            
            for line_num, line in o_files:
                output_lines.append(f"Line {line_num:4d}: {line}")
            
            # Output to console
            for line in output_lines:
                print(line)
            
            # Save to file if specified
            if output_file:
                try:
                    with open(output_file, 'w', encoding='utf-8') as f:
                        f.write('\n'.join(output_lines) + '\n')
                    print(f"\nResults saved to: {output_file}")
                except Exception as e:
                    print(f"Error saving to file: {e}")
        else:
            print("No lines ending with .o: found.")
            
    except Exception as e:
        print(f"Error reading file: {e}")

def main():
    parser = argparse.ArgumentParser(description='Find lines ending with .o: in splits.txt')
    parser.add_argument('--output', '-o', help='Save results to a file')
    parser.add_argument('--filter', '-f', help='Filter results by text pattern')
    parser.add_argument('--count-only', '-c', action='store_true', help='Only show the count of matches')
    
    args = parser.parse_args()
    
    find_o_files(
        output_file=args.output,
        filter_text=args.filter,
        count_only=args.count_only
    )

if __name__ == "__main__":
    if len(sys.argv) == 1:
        # No arguments provided, run with default behavior
        find_o_files()
    else:
        main()
