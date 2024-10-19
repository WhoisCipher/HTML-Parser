# HTML Parser

HTML Parser is a simple command-line interface (CLI) tool designed to determine if an HTML file or string is correctly formatted. This tool helps you quickly validate HTML structures and identify mismatched tags.

## Features

- Validates HTML files or strings.
- Provides feedback on formatting correctness.

## How to Use

HTML Parser supports two command-line switches:

### 1. File Input (`-f`)

Use this option to validate an HTML file.

```bash
htmp -f <filename>
```

**Example:**
```bash
htmp -f example.html
```

### 2. String Input (`-s`)

Use this option to validate a string of HTML.

```bash
htmp -s "<html><body></body></html>"
```

**Example:**
```bash
htmp -s "<div><p>Hello World</p></div>"
```

## Installation

### Prerequisites

Ensure you have a C++ compiler installed on your system (e.g., g++, clang++).

### Steps to Install

1. **Clone the Repository** (if applicable):
   ```bash
   git clone https://github.com/yourusername/HTML-Parser.git
   cd HTML-Parser
   ```

2. **Compile the Program**:
   ```bash
   g++ html_parser.cpp -o htmp
   ```

3. **Move to a Directory in Your PATH** (optional):
   ```bash
   sudo mv htmp /usr/local/bin/
   ```

### Alternative Installation via CMake

If you prefer to use CMake for building the project, you can do so as follows:

```bash
mkdir build
cd build
cmake ..
make
```

## Example Usage

To check an HTML file:
```bash
htmp -f myfile.html
```

To check an inline HTML string:
```bash
htmp -s "<html><body><h1>Hello World</h1></body></html>"
```

## Output

The program will output whether the HTML is correctly formatted or not:
- **Formatted Correctly**: Indicates that all tags are properly closed and nested.
- **Format INCORRECT!**: Indicates there are mismatched or unclosed tags.


## Contact

For any questions or feedback, feel free to reach out:

- **Abdullah**: [me@gmail.com](mailto:khan.abdullah.shoaib@gmail.com)
- **GitHub**: [WhoisCipher](https://github.com/WhoisCipher)
