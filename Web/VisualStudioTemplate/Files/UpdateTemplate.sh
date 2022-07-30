#/bin/bash

folders=(
    "example"
    "resources"
)

function CopyFromAppFolder() {
    for folder in "${folders[@]}"; do
        cp -r ../../App/${folder} .
    done

    cp -r ../../App/Templates .
}

function ReplaceVSTemplate() {
    local Items=""

    for folder in "${folders[@]}"; do
        for item in `find ${folder} -type f | sort`; do
            filename=`basename ${item}`
            foldername=`dirname ${item}`
            Items+="      <ProjectItem ReplaceParameters=\"false\" TargetFileName=\"${filename}\">${item}</ProjectItem>\n"
        done
    done

    sed -e "s|\${Items}|${Items}|g" MyTemplate.vstemplate.tpl > MyTemplate.vstemplate
}

function ReplaceVCXProj() {
    local ResourcesItems=""

    for item in `find resources -type f | sort`; do
        filename=`basename ${item}`
        foldername=`dirname ${item}`
        ResourcesItems+="    <None Include=\"${item//\//\\\\}\" />\n"
    done

    sed -e "s|\${ResourcesItems}|${ResourcesItems}|g" Siv3DTest.vcxproj.tpl > Siv3DTest.vcxproj

    local ExampleItems=""

    for item in `find example -type f | sort`; do
        filename=`basename ${item}`
        foldername=`dirname ${item}`
        ExampleItems+="    <None Include=\"${item//\//\\\\}\" />\n"
    done

    sed -i -e "s|\${ExampleItems}|${ExampleItems}|g" Siv3DTest.vcxproj
}

function ReplaceVCXProjFilter() {
    local ResourcesItems=""

    for item in `find resources -type f | sort`; do
        filename=`basename ${item}`
        foldername=`dirname ${item}`
        ResourcesItems+="    <None Include=\"${item//\//\\\\}\">\n"
        ResourcesItems+="      <Filter>Resource Files\\\\${foldername//\//\\\\}</Filter>\n"
        ResourcesItems+="    </None>\n"
    done

    sed -e "s|\${ResourcesItems}|${ResourcesItems}|g" Siv3DTest.vcxproj.filters.tpl > Siv3DTest.vcxproj.filters

    local ExampleItems=""

    for item in `find example -type f | sort`; do
        filename=`basename ${item}`
        foldername=`dirname ${item}`
        ExampleItems+="    <None Include=\"${item//\//\\\\}\">\n"
        ExampleItems+="      <Filter>Resource Files\\\\${foldername//\//\\\\}</Filter>\n"
        ExampleItems+="    </None>\n"
    done

    sed -i -e "s|\${ExampleItems}|${ExampleItems}|g" Siv3DTest.vcxproj.filters
}


CopyFromAppFolder
ReplaceVSTemplate
ReplaceVCXProj
ReplaceVCXProjFilter
