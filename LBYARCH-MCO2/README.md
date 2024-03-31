# LBYARCH MCO2 Code Overview

This project implements the dot product of two vectors with the use of C-Assembly interfacing. A comparative analysis of the running time of C and x86-64 Assembly kernels was also done.

## How to run the Code
1. Download `main.c`, `c_dot_product.c`, and `asm_dot_product.asm`.
2. Make sure `asm_dot_product.asm` is configured properly to interface with C.
3. Run `main.c`.
4. After running `main.c`, it will create a folder in the same directory with the results in a CSV file.

## Comparative Analysis
### Debug Mode
#### x86-64 Assembly
| Vector Size | Average Run Time |
|:---:|:---:|
| 2<sup>20</sup> | 0.000767s |
| 2<sup>24</sup> | 0.012492s |
| 2<sup>30</sup> | 0.751183s |

CSV File of all Runs of Each Vector Size: [Link](https://drive.google.com/file/d/1FIY2kaOn_LnYiFPfFlEJesJDotYEDWf_/view?usp=sharing)

#### C 
| Vector Size | Average Run Time |
|:---:|:---:|
| 2<sup>20</sup> | 0.003000s |
| 2<sup>24</sup> | 0.049000s |
| 2<sup>30</sup> | 2.942500s |

CSV File of all Runs of Each Vector Size: [Link](https://drive.google.com/file/d/11DLMh-nUxmdzDPbEfMPzxMoUUSx60SyH/view?usp=sharing)

In debug mode, the x86-64 Assembly implementation showed faster run times than the C implementation across all vector sizes. Specifically, for vector sizes of 2^20, 2^24, and 2^30, the average run times in x86-64 Assembly were 0.000767s, 0.012492s, and 0.751183s, respectively. In contrast, the C implementation reported longer run times of 0.003000s, 0.049000s, and 2.942500s for the same vector sizes. This test showed that Assembly runs at least three to four times faster compared to C.

#### Screenshot of Program Output
[![image.png](https://i.postimg.cc/gJH4W8GM/image.png)](https://postimg.cc/G89vPB8Y)

### Release Mode
#### x86-64 Assembly
| Vector Size | Average Run Time |
|:---:|:---:|
| 2<sup>20</sup> | 0.000733s |
| 2<sup>24</sup> | 0.012058s |
| 2<sup>30</sup> | 0.750669s |

CSV File of all Runs of Each Vector Size: [Link](https://drive.google.com/file/d/1qD9dh1QIcC9OI8j4Vh1913g4mrV8eqsA/view?usp=sharing)

#### C 
| Vector Size | Average Run Time |
|:---:|:---:|
| 2<sup>20</sup> | 0.000000s |
| 2<sup>24</sup> | 0.000000s |
| 2<sup>30</sup> | 0.000000s |

CSV File of all Runs of Each Vector Size: [Link](https://drive.google.com/file/d/1i5jsDcSS6l_yfqA8u7M0BGs6swCKqmcL/view?usp=sharing)

For release mode, the average run times for the x86-64 Assembly implementation for vector sizes of 2^20, 2^24, and 2^30 were 0.000733s, 0.012058s, and 0.750669s respectively. On the other hand, the C implementation returned run times of 0.000000s across all vector sizes in this mode, which could indicate that it ran so fast that the test could not record it. This showed a significant increase in performance compared to debug mode.

#### Screenshot of Program Output
[![Release.png](https://i.postimg.cc/tTBRwvn2/image.png)](https://postimg.cc/r0tLtJJr)