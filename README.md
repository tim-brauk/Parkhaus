```text
parkhaus-simulation/
│
├── README.md
├── LICENSE
├── (Makefile)
│
├── docs/
│   ├── pseudocode/
│   │   ├── Functions.txt
│   │   ├── statistiken_funktionen.txt
│   │   └── StructsDatentypen.txt
│   ├── diagrams/
│       ├── Flussdiagramm_entferne_kfzs_maximale_parkdauer
│       ├── Flussdiagramm_fuege_kfz_hinzu
│       └── Flussdiagramm_kfz_hinzufuegen_warteschlange
│   
│
├── include/
│   ├── kfz.h
│   ├── parkhaus.h
│   ├── parkvorgang.h
│   ├── simulation.h
│   ├── statistiken.h
│   └── warteschlange.h
│
├── src/
│   ├── main.c
│   ├── kfz.c
│   ├── parkhaus.c
│   ├── parkvorgang.c
│   ├── simulation.c
│   ├── statistiken.c
│   └── warteschlange.c
│
├── tests/
│   └── (...)
│
└── .github/
└── workflows/
└── (build.yml)
```