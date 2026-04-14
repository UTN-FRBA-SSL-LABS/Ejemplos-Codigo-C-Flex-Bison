#!/bin/sh

# Gets the relative directory of the current script
this_dir=$(dirname "$0")

# Includes color definitions
. "${this_dir}/colors.sh"

. "${this_dir}/settings.sh"

# Validar la cantidad recibida de parámetros
if [ "$#" -ne 1 ]; then
    printf "${Yellow}Uso: $0 <ruta al programa>${Color_Off}\n"
    exit 1
fi

program_path="$1"

# Variables contadoras
total_tests=0
passed_tests=0
total_percentage=0

if ! [ -f "$program_path" ]; then
    printf "${Yellow}No existe el programa objetivo: '%s'. Se lo debe construir primero...${Color_Off}\n" "$program_path"
    exit 1
fi

chmod +x "${program_path}"

# Ejecutar pruebas
for input_path in "${this_dir}"/input/test_*"${input_extension}"; do
    total_tests=$(expr "$total_tests" + 1)
    test_name=$(basename "${input_path}" ${input_extension})
    actual_output_path="${this_dir}/output/${test_name}.txt"
    expected_output_path="${this_dir}/output/expected/${test_name}.txt"

    printf "${Purple}Ejecutando %s...${Color_Off}\n\n" "${test_name}"

    if ! [ -f "$expected_output_path" ]; then
        printf "\n${Yellow}No existe el archivo de salida esperada: '%s'${Color_Off}\n" "$expected_output_path"
        break
    fi

    # Ejecutar el programa con rutas de archivo de entrada y salida
    '${program_path}' '${input_path}' > '${actual_output_path}'

    if ! [ -f "$actual_output_path" ]; then
        printf "\n${Yellow}No existe el archivo de salida actual: "%s"${Color_Off}\n" "$actual_output_path"
        break
    fi

        # Normalizar ambos archivos (reemplazar \r\n por \n, limpieza de tabulaciones, espacios, eliminar líneas vacías)
        sed -e 's/\r$//' -e 's/\t/ /g' -e 's/^[[:space:]]*//' -e 's/[[:space:]]*$//' -e 's/[[:space:]]\{2,\}/ /g' -e '/^$/d' -e '$a\' "$actual_output_path" > "${this_dir}/output/${test_name}_clean.txt"
        sed -e 's/\r$//' -e 's/\t/ /g' -e 's/^[[:space:]]*//' -e 's/[[:space:]]*$//' -e 's/[[:space:]]\{2,\}/ /g' -e '/^$/d' -e '$a\' "$expected_output_path" > "${this_dir}/output/expected/${test_name}_clean.txt"

        # Contar líneas en los archivos limpios
        output_line_count=$(wc -l < "${this_dir}/output/${test_name}_clean.txt")
        expected_line_count=$(wc -l < "${this_dir}/output/expected/${test_name}_clean.txt")

    # Usar diff para encontrar diferencias ignorando líneas vacías y normalizadas y contar las líneas coincidentes del output de la ejecución respecto del esperado
    matching_lines=$(expr "$expected_line_count" - "$(diff "${this_dir}/output/${test_name}_clean.txt" "${this_dir}/output/expected/${test_name}_clean.txt" | grep -c '^>')")

    # Calcular porcentaje de coincidencia
    percentage_matching=0
    [ "$expected_line_count" -gt 0 ] && [ "$output_line_count" -gt 0 ] && {
        percentage_matching_expected=$(awk -v a="$matching_lines" -v b="$expected_line_count" 'BEGIN {printf "%.2f", (a / b) * 100}')
        percentage_matching_output=$(awk -v a="$matching_lines" -v b="$output_line_count" 'BEGIN {printf "%.2f", (a / b) * 100}')
        percentage_matching=$(awk -v a="$percentage_matching_expected" -v b="$percentage_matching_output" 'BEGIN {printf "%.2f", (a < b ? a : b)}')
    }

    # Sumarizar para promedio
    total_percentage=$(awk -v a="$total_percentage" -v b="$percentage_matching" 'BEGIN {print a + b}')

    # Determinar si el test es pasado o no basado en el porcentaje de coincidencia
    if awk -v a="$percentage_matching" -v b="$min_percentage_matching_per_test" 'BEGIN {exit !(a >= b)}'; then
        passed_tests=$(expr "$passed_tests" + 1)
        printf "\nResultado de ${test_name}:${Green} PASS con ${percentage_matching}%% de cobertura${Color_Off}\n"
    else
        printf "\nResultado de %s:${Red} FAIL con %s%% de cobertura. Minimo a alcanzar para superar test: %s%%${Color_Off}\n" "$test_name" "$percentage_matching" "$min_percentage_matching_per_test"
    fi

    if ! command -v git >/dev/null 2>&1; then
        printf "\nDiferencias entre salida actual y salida esperada:\n"
        diff "${this_dir}/output/${test_name}_clean.txt" "${this_dir}/output/expected/${test_name}_clean.txt"
    else
        printf "\nDiferencias indicadas segun colores de referencia:\n${Color_Off}  * Color por defecto: Informacion${Color_Off}\n${Cyan}  * Cian: Numeros de lineas con diferencias entre salida actual y esperada${Color_Off}\n${Red}  - Rojo: Lineas diferentes en salida actual${Color_Off}\n${Green}  + Verde: Lineas diferentes en salida esperada${Color_Off}\n"
        git --no-pager diff --no-index --unified=0 "${this_dir}/output/${test_name}_clean.txt" "${this_dir}/output/expected/${test_name}_clean.txt"
    fi
    
done

# Calcular el porcentaje promedio de coincidencia
if [ "$total_tests" -ne 0 ]; then
    average_percentage=$(awk -v a="$total_percentage" -v b="$total_tests" 'BEGIN {printf "%.2f", a / b}')
else
    average_percentage=0
fi

printf "\nSe supero %s test(s) de un total de %s test(s)\n" "$passed_tests" "$total_tests"
printf "\nPorcentaje promedio de cobertura de tests: %s%%\n" "$average_percentage"

if awk -v a="$passed_tests" -v b="$min_quantity_test" 'BEGIN {exit !(a < b)}'; then
    pass_tests=0
    printf "\n${Red}No se supero la cantidad minima de test para revision de PR. Superar como minimo %s de %s${Color_Off}\n\n" "$min_quantity_test" "$total_tests"
    exit 1
fi

if awk -v a="$average_percentage" -v b="$min_average_percentage_over_all_test" 'BEGIN {exit !(a <= b)}'; then
    pass_tests=0
    printf "\n${Red}No se alcanzo el minimo porcentaje promedio de cobertura de tests para revision de PR. Minimo de porcentaje promedio de cobertura requerido: %s%%${Color_Off}\n\n" "$min_average_percentage_over_all_test"
    exit 1
fi

if [ "$pass_tests" -ne 0 ]; then
    printf "\n${Green}Se superaron los requerimientos de los tests, puede continuarse con revision de PR${Color_Off}\n\n"
    exit 0
fi
