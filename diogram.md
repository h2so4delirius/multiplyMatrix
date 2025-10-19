# Diagram pro maticové násobení

```mermaid
graph TD
    A[Start] --> B{width_1 != height_2?};
    B -- Ano --> C[return nullptr];
    B -- Ne --> D[double * result = new double[width_2 * height_1]];
    D --> E[for i = 0 to height_1 * width_2];
    E --> F[result[i] = 0.0];
    F --> E;
    E --> G[for i = 0 to height_1];
    G --> H[for j = 0 to width_2];
    H --> I[for k = 0 to width_1];
    I --> J[result[i * width_2 + j] += ...];
    J --> I;
    I --> H;
    H --> G;
    G --> K[return result];
    K --> L[End];
    C --> L;
```
