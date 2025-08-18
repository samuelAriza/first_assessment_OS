import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import os
from pathlib import Path

# Configuración
sns.set(style="whitegrid")
plt.rcParams.update({'font.size': 10, 'figure.dpi': 300})

# Directorios de los CSVs
BASE_DIR = Path('benchmarks')
# CSV tal como los produce el proyecto (sin requerir carpeta "normalized")
SUMMARY_CSV = BASE_DIR / 'results_summary.csv'
STRUCT_CSV = BASE_DIR / 'results_struct.csv'
CLASS_CSV = BASE_DIR / 'results_class.csv'
ISOLATED_SUMMARY_CSV = BASE_DIR / 'isolated' / 'results_summary.csv'
ISOLATED_STRUCT_CSV = BASE_DIR / 'isolated' / 'results_struct.csv'
ISOLATED_CLASS_CSV = BASE_DIR / 'isolated' / 'results_class.csv'
OUTPUT_DIR = BASE_DIR / 'plots'
OUTPUT_DIR.mkdir(exist_ok=True)

# Leer CSVs con manejo de errores
def load_csv(file_path):
    try:
        df = pd.read_csv(file_path)
        if df.empty:
            print(f"Advertencia: {file_path} está vacío")
            return None
        return df
    except FileNotFoundError:
        print(f"Error: {file_path} no encontrado")
        return None
    except pd.errors.EmptyDataError:
        print(f"Error: {file_path} está vacío o tiene formato inválido")
        return None

summary_df = load_csv(SUMMARY_CSV)
struct_df = load_csv(STRUCT_CSV)
class_df = load_csv(CLASS_CSV)
isolated_summary_df = load_csv(ISOLATED_SUMMARY_CSV)
isolated_struct_df = load_csv(ISOLATED_STRUCT_CSV)
isolated_class_df = load_csv(ISOLATED_CLASS_CSV)

# Lista de métricas
metrics = ['Wall_ms', 'CPU_ms', 'HeapKB_Delta', 'RSSKB_Delta']
metric_labels = {
    'Wall_ms': 'Tiempo real (ms)',
    'CPU_ms': 'Tiempo de CPU (ms)',
    'HeapKB_Delta': 'Cambio en memoria del montón (KB)',
    'RSSKB_Delta': 'Cambio en memoria residente (KB)'
}

def derive_mode(func: str, impl: str) -> str:
    if isinstance(func, str):
        if func.endswith('_ptr'): return 'ptr'
        if func.endswith('_val'): return 'val'
    if isinstance(impl, str):
        if '(ptr)' in impl: return 'ptr'
        if '(val)' in impl: return 'val'
    return ''

def base_func(func: str) -> str:
    if not isinstance(func, str):
        return ''
    if func.endswith('_ptr'): return func[:-4]
    if func.endswith('_val'): return func[:-4]
    return func

def lang_from_impl(impl: str) -> str:
    if isinstance(impl, str) and 'C++' in impl:
        return 'C++'
    return 'C'

FUNC_MAP = {
    'listTaxGroup_ptr': 'listByGroup_ptr',
    'listTaxGroup_val': 'listByGroup_val',
    'countTaxGroup_ptr': 'countByGroup_ptr',
    'countTaxGroup_val': 'countByGroup_val',
}

def normalize_columns(df: pd.DataFrame) -> pd.DataFrame:
    d = df.copy()
    # Renombrar columnas legadas a las nuevas
    if 'Time_ms' in d.columns and 'Wall_ms' not in d.columns:
        d = d.rename(columns={'Time_ms': 'Wall_ms'})
    if 'Mem_KB' in d.columns and 'RSSKB_Delta' not in d.columns:
        d = d.rename(columns={'Mem_KB': 'RSSKB_Delta'})
    # Asegurar columnas obligatorias
    for col, default in (
        ('CPU_ms', 0),
        ('HeapKB_Delta', 0),
        ('RSSKB_Delta', 0),
        ('Wall_ms', 0),
    ):
        if col not in d.columns:
            d[col] = default
    # Normalizar nombres de funciones entre C y C++
    if 'Function' in d.columns:
        d['Function'] = d['Function'].map(lambda f: FUNC_MAP.get(f, f))
    # Tipos numéricos
    if 'N' in d.columns:
        d['N'] = pd.to_numeric(d['N'], errors='coerce')
    for m in ('Wall_ms','CPU_ms','HeapKB_Delta','RSSKB_Delta'):
        if m in d.columns:
            d[m] = pd.to_numeric(d[m], errors='coerce')
    return d

# ==============================
# Gráficos: una imagen por función y métrica
# ==============================
def enrich(df: pd.DataFrame) -> pd.DataFrame:
    if df is None:
        return None
    d = normalize_columns(df)
    d['Mode'] = [derive_mode(f, i) for f, i in zip(d.get('Function',''), d.get('Implementation',''))]
    d['FunctionBase'] = [base_func(f) for f in d.get('Function','')]
    d['Language'] = [lang_from_impl(i) for i in d.get('Implementation','')]
    # Unificar etiqueta de implementación a solo lenguaje para evitar variaciones (C (ptr), C++ (class), etc.)
    d['ImplementationNorm'] = d['Language']
    return d

def plot_results(df, prefix, metrics):
    if df is None:
        return
    d = enrich(df)
    if d is None or d.empty:
        return
    # Para cada función base y N, graficar barras de C-ptr, C-val, C++-ptr, C++-val si existen
    funcs = sorted(d['FunctionBase'].dropna().unique())
    for metric in metrics:
        for func in funcs:
            sub = d[d['FunctionBase'] == func]
            for n in sorted(sub['N'].dropna().unique()):
                subn = sub[sub['N'] == n]
                if subn.empty:
                    continue
                # orden consistente
                subn = subn.sort_values(by=['Language', 'Mode'])
                plot_df = pd.DataFrame({
                    'Label': [f"{lang}-{mode}" for lang, mode in zip(subn['Language'], subn['Mode'])],
                    'Value': subn[metric].values
                })
                # Filtrar valores nulos o cero (solo graficar si hay diferencias de 0)
                plot_df = plot_df[pd.to_numeric(plot_df['Value'], errors='coerce').fillna(0) != 0]
                if plot_df.empty:
                    continue
                plt.figure(figsize=(7, 4))
                sns.barplot(data=plot_df, x='Label', y='Value', hue='Label', dodge=False, legend=False, palette='Set2')
                plt.title(f"{func} @ N={int(n)} - {metric_labels[metric]}")
                plt.ylabel(metric_labels[metric])
                plt.xlabel('Lenguaje-Modo')
                plt.axhline(0, color='gray', linewidth=0.5)
                plt.tight_layout()
                plt.savefig(OUTPUT_DIR / f'{prefix}_{func}_N{int(n)}_{metric}.png')
                plt.close()

# Ejecutar para cada dataset
plot_results(summary_df, "summary", metrics)
plot_results(isolated_summary_df, "isolated", metrics)

# Gráficas de razón val/ptr por lenguaje (speedups): val/ptr (Wall_ms, CPU_ms, Heap/RSS)
def plot_speedups(df, prefix):
    if df is None:
        return
    d = enrich(df)
    if d is None or d.empty:
        return
    for metric in metrics:
        piv = d.pivot_table(index=['FunctionBase','N','Language'], columns='Mode', values=metric, aggfunc='mean').reset_index()
        if 'ptr' not in piv or 'val' not in piv:
            continue
        piv['val_over_ptr'] = piv['val'] / piv['ptr']
        # Filtrar NaN, inf y ceros (no graficar si todo es 0 o inválido)
        piv = piv.replace([pd.NA, pd.NaT, float('inf'), -float('inf')], pd.NA)
        for lang in sorted(piv['Language'].unique()):
            sub = piv[piv['Language']==lang]
            if sub.empty:
                continue
            plt.figure(figsize=(9,4))
            g = sub.groupby('FunctionBase')['val_over_ptr'].mean().reset_index()
            g = g[pd.to_numeric(g['val_over_ptr'], errors='coerce').notna()]
            g = g[g['val_over_ptr'] != 0]
            if g.empty:
                plt.close()
                continue
            sns.barplot(data=g, x='FunctionBase', y='val_over_ptr', color='#4E79A7')
            plt.axhline(1.0, color='gray', linestyle='--', linewidth=1)
            plt.ylabel(f'{metric_labels[metric]} val/ptr ({lang})')
            plt.xlabel('Función')
            plt.xticks(rotation=45, ha='right')
            plt.tight_layout()
            plt.savefig(OUTPUT_DIR / f'{prefix}_speedup_{metric}_{lang}.png')
            plt.close()

plot_speedups(summary_df, 'summary')
plot_speedups(isolated_summary_df, 'isolated')
