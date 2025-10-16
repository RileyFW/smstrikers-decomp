#!/usr/bin/env python3
"""
Script to find all *.cpp files in dwarf_ouput2.txt and match them with *.o files from splits.txt
Shows the file and the last 2 directories in their path for each *.o file

Usage:
    python3 find_cpp_files.py [options]

Options:
    --output FILE    Save results to a file
    --filter TEXT    Filter results by text pattern
    --count-only     Only show the count of matches
    --help           Show this help message
"""

import os
import sys
import argparse
import re
from pathlib import Path

def extract_cpp_files_from_dwarf():
    """Extract all .cpp files from dwarf_ouput2.txt"""
    dwarf_file = "dwarf_ouput2.txt"
    
    if not os.path.exists(dwarf_file):
        print(f"Error: {dwarf_file} not found!")
        return []
    
    cpp_files = []
    
    try:
        with open(dwarf_file, 'r', encoding='utf-8') as f:
            for line_num, line in enumerate(f, 1):
                line = line.strip()
                # Look for "Compile unit:" lines that contain .cpp files
                if line.startswith("Compile unit:") and ".cpp" in line:
                    # Extract the file path
                    match = re.search(r'Compile unit:\s+(.+)', line)
                    if match:
                        file_path = match.group(1).strip()
                        cpp_files.append((line_num, file_path))
        
        print(f"Found {len(cpp_files)} .cpp files in dwarf_ouput2.txt")
        return cpp_files
        
    except Exception as e:
        print(f"Error reading dwarf file: {e}")
        return []

def extract_cpp_and_o_files_from_splits():
    """Extract all .cpp and .o files from splits.txt"""
    splits_file = "config/G4QE01/splits.txt"
    
    if not os.path.exists(splits_file):
        print(f"Error: {splits_file} not found!")
        return [], []
    
    cpp_files = []
    o_files = []
    
    try:
        with open(splits_file, 'r', encoding='utf-8') as f:
            for line_num, line in enumerate(f, 1):
                line = line.strip()
                if line.endswith('.cpp:'):
                    # Remove the colon at the end
                    cpp_file = line[:-1]
                    cpp_files.append((line_num, cpp_file))
                elif line.endswith('.o:'):
                    # Remove the colon at the end
                    o_file = line[:-1]
                    o_files.append((line_num, o_file))
        
        print(f"Found {len(cpp_files)} .cpp files and {len(o_files)} .o files in splits.txt")
        return cpp_files, o_files
        
    except Exception as e:
        print(f"Error reading splits file: {e}")
        return [], []

def get_last_two_directories(file_path):
    """Get the last 2 directories from a file path"""
    # Normalize Windows paths
    normalized_path = file_path.replace('\\', '/')
    path = Path(normalized_path)
    parts = path.parts
    
    if len(parts) >= 3:
        return "/".join(parts[-3:-1])  # Last 2 directories
    elif len(parts) == 2:
        return parts[0]  # Only one directory
    else:
        return "."

def match_o_files_with_cpp_paths(dwarf_cpp_files, splits_o_files, filter_text=None, count_only=False):
    """Match .o files with their corresponding .cpp files from dwarf and show the path mapping"""
    matches = []
    
    # Create a mapping of .o files to their corresponding .cpp files
    for line_num, o_file in splits_o_files:
        # Remove .o extension for matching with dwarf cpp files
        o_stem = o_file.replace('.o', '')
        
        # Find matching .cpp file in dwarf
        matching_cpp = None
        for dwarf_line, cpp_path in dwarf_cpp_files:
            # Extract filename without extension
            cpp_path_normalized = cpp_path.replace('\\', '/')
            cpp_stem = Path(cpp_path_normalized).stem
            
            if cpp_stem == o_stem:
                matching_cpp = cpp_path
                break
        
        if matching_cpp:
            # Extract the path part after "global" or "project"
            path_parts = matching_cpp.replace('\\', '/').split('/')
            
            # Find the index of "global" or "project" in the path
            start_idx = -1
            for i, part in enumerate(path_parts):
                if part.lower() in ['global', 'project']:
                    start_idx = i
                    break
            
            if start_idx != -1 and start_idx + 1 < len(path_parts):
                # Get the path starting from after "global" or "project"
                relative_path = '/'.join(path_parts[start_idx + 1:])
                # Convert back to Windows-style path
                relative_path = relative_path.replace('/', '\\')
            else:
                # Fallback to just the filename
                relative_path = Path(matching_cpp).name
            
            match_info = {
                'o_file': o_file,
                'cpp_path': matching_cpp,
                'relative_path': relative_path,
                'dwarf_line': dwarf_line
            }
            
            # Apply filter if specified
            if filter_text is None or filter_text.lower() in o_file.lower() or filter_text.lower() in matching_cpp.lower():
                matches.append(match_info)
    
    if count_only:
        print(f"Found {len(matches)} .o files with matching .cpp paths")
        return
    
    if matches:
        output_lines = []
        output_lines.append(f"Found {len(matches)} .o files with matching .cpp paths:")
        output_lines.append("=" * 80)
        
        for match in matches:
            output_lines.append(f"{match['o_file']} -> {match['relative_path']}")
        
        # Output to console
        for line in output_lines:
            print(line)
        
        return output_lines
    else:
        print("No matching .o files with .cpp paths found.")
        return []

def find_cpp_files(output_file=None, filter_text=None, count_only=False):
    """Main function to find and match .o files with .cpp files"""
    print("Extracting .cpp files from dwarf_ouput2.txt...")
    dwarf_cpp_files = extract_cpp_files_from_dwarf()
    
    if not dwarf_cpp_files:
        return
    
    print("Extracting .o files from splits.txt...")
    splits_cpp_files, splits_o_files = extract_cpp_and_o_files_from_splits()
    
    if not splits_o_files:
        return
    
    print("Matching .o files with .cpp paths...")
    output_lines = match_o_files_with_cpp_paths(dwarf_cpp_files, splits_o_files, filter_text, count_only)
    
    # Save to file if specified
    if output_file and output_lines:
        try:
            with open(output_file, 'w', encoding='utf-8') as f:
                f.write('\n'.join(output_lines) + '\n')
            print(f"\nResults saved to: {output_file}")
        except Exception as e:
            print(f"Error saving to file: {e}")

def main():
    parser = argparse.ArgumentParser(description='Find and match .cpp files with .o files')
    parser.add_argument('--output', '-o', help='Save results to a file')
    parser.add_argument('--filter', '-f', help='Filter results by text pattern')
    parser.add_argument('--count-only', '-c', action='store_true', help='Only show the count of matches')
    
    args = parser.parse_args()
    
    find_cpp_files(
        output_file=args.output,
        filter_text=args.filter,
        count_only=args.count_only
    )

if __name__ == "__main__":
    if len(sys.argv) == 1:
        # No arguments provided, run with default behavior
        find_cpp_files()
    else:
        main()
