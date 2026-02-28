```
parkhaus-simulation/
│
├── README.md
├── LICENSE
├── (Makefile)
│
├── docs/
│   ├── pseudocode/
│   │   ├── Functions.txt
│   │   └── StructsDatentypen.txt
│   ├── diagrams/
│   │   └── ...
│   └── statistics_concept.md
│
├── include/
│   ├── kfz.h
│   ├── parkhaus.h
│   ├── parkvorgang.h
│   ├── simulation.h
│   └── warteschlange.h
│
├── src/
│   ├── (main.c)
│   ├── (kfz.c)
│   ├── (parkhaus.c)
│   ├── (parkvorgang.c)
│   ├── (simulation.c)
│   └── (warteschlange.c)
│
├── tests/
│   └── (...)
│
└── .github/
    └── workflows/
        └── (build.yml)
```