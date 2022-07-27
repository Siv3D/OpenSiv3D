#!/bin/bash

TargetFiles=(
    "../VisualStudioTemplate/Files/Siv3DTest.vcxproj"
    "../VisualStudioTemplate/Files/MyTemplate.vstemplate"
    "../WindowsInstaller/setup.iss"
    "../../.github/workflows/ccpp_web.yml"
)

function getCurrentVersion() {
    local Tags=(`git tag | awk 'match($0, /v([0-9\.]+)[rb\.]([0-9]+)/, a) { print a[1]"."a[2] }' | sort --reverse`)
    echo ${Tags[0]}
}

function bumpVersion() {
    local SplittedCurrentVersion=(${1//./ })

    local major=${SplittedCurrentVersion[0]}
    local minor=${SplittedCurrentVersion[1]}
    local patch=${SplittedCurrentVersion[2]}
    local revision=${SplittedCurrentVersion[3]:=0}

    case "${2}" in
        major)
            let ++major
            minor=0
            patch=0
            revision=0;;
        minor)
            let ++minor
            patch=0
            revision=0;;
        patch)
            let ++patch
            revision=0;;
        revision)
            let ++revision;;
    esac

    echo "${major}.${minor}.${patch}.${revision}"
}

function trimRevision() {
    local SplittedCurrentVersion=(${1//./ })

    local major=${SplittedCurrentVersion[0]}
    local minor=${SplittedCurrentVersion[1]}
    local patch=${SplittedCurrentVersion[2]}

    echo "${major}.${minor}.${patch}"
}

function main() {
    local currentVersion=`getCurrentVersion`
    local newVersion=`bumpVersion ${currentVersion} $@`

    local shortCurrentVersion=`trimRevision ${currentVersion}`
    local shortNewVersion=`trimRevision ${newVersion}`

    echo "bumping ${currentVersion} to ${newVersion} ..."

    for file in "${TargetFiles[@]}"; do
        sed -i -e "s/${currentVersion//./\\.}/${newVersion}/g" $file
        sed -i -e "s/${shortCurrentVersion//./\\.}/${shortNewVersion}/g" $file
        sed -i -e "s/${shortCurrentVersion//./_}/${shortNewVersion//./_}/g" $file
    done
}

main $@
