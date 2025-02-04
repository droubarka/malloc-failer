[![Status: In Development](https://img.shields.io/badge/Status-In%20Development-blue)]()
[![Last Commit](https://img.shields.io/github/last-commit/droubarka/malloc-failer)]()
[![License: GPLv3](https://img.shields.io/badge/License-GPLv3-green.svg)](https://www.gnu.org/licenses/gpl-3.0.en.html#license-text)

# malloc-failer
**malloc-failer** is a custom memory allocation wrapper that logs memory allocation failures. It tracks the file, function, and line number where the allocation fails and can write the logs to a specified log file (default: xmalloc.log). The project also allows the user to specify certain lines in the code to always log memory allocation attempts, providing better insight into memory management issues during debugging.

## Usage
Clone the repo and navigate into the project:
```bash
git clone https://github.com/droubarka/malloc-failer.git
cd malloc-failer
```

Compile with custom macros for specific lines and log file:
```bash
make MACROS='-D SPECIFICLINES=7,8 -D LOGFILE=\"logfile.log\"'
```

Link your project with the xmalloc static library:
```bash
gcc YOURPROJECT.c xmalloc -o YOURPROJECT
```

Example Output for `YOURPROJECT`
```c
#include <stdio.h>
#include <stdlib.h>
#include "xmalloc.h"

int main() {
    char *ptr1 = malloc(100); // Normal allocation
    char *ptr2 = malloc(50);  // Assume this is line 7
    char *ptr3 = malloc(200); // Assume this is line 8

    // No NULL check, leading to a segmentation fault if malloc fails
    ptr2[0] = 'A';
    ptr3[0] = 'B';

    free(ptr1);
    free(ptr2);
    free(ptr3);

    return 0;
}
```

And you compile with:
```bash
make MACROS='-D SPECIFICLINES=7,8 -D LOGFILE=\"logfile.log\"'
gcc YOURPROJECT.c xmalloc -o YOURPROJECT
./YOURPROJECT
```

Expected Terminal Output (`stderr`):
```bash
xmalloc: YOURPROJECT.c:main:7: unable to allocate 50 Bytes
xmalloc: YOURPROJECT.c:main:8: unable to allocate 200 Bytes
Segmentation fault (core dumped)

xmalloc: note: Log has been successfully saved to logfile.log
```

Contents of `logfile.log`:
```bash
xmalloc: YOURPROJECT.c:main:7: unable to allocate 50 Bytes
xmalloc: YOURPROJECT.c:main:8: unable to allocate 200 Bytes
```

Explanation:
- Lines 7 and 8 fail due to SPECIFICLINES, so malloc returns NULL.
- No NULL check means the program tries to access ptr2[0] and ptr3[0], causing a segmentation fault.
- Log file still records the failures, providing a clue for debugging.
- The final log message appears before the crash, ensuring logs are saved.

## License
**malloc-failer** is licensed under the GPLv3 License. See [LICENSE](LICENSE) for details.
