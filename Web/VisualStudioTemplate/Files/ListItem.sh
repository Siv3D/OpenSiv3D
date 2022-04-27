#/bin/bash

folders=(
    "resources"
    "example"
)

for folder in "${folders[@]}"; do
    for item in `find ${folder} -type f | sort`; do
        filename=`basename ${item}`
        foldername=`dirname ${item}`
        # echo "      <ProjectItem ReplaceParameters=\"false\" TargetFileName=\"${filename}\">${item}</ProjectItem>"
        echo "    <None Include=\"${item//\//\\}\" />"
        # echo "    <None Include=\"${item//\//\\}\">"
        # echo "      <Filter>Resource Files\\${foldername//\//\\}</Filter>"
        # echo "    </None>"
    done
done
