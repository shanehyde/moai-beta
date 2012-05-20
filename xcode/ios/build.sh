#!/bin/bash

#----------------------------------------------------------------#
# Copyright (c) 2010-2011 Zipline Games, Inc.
# All Rights Reserved.
# http://getmoai.com
#----------------------------------------------------------------#

set -e

usage="usage: $0 [-j <jobName>] [-c Debug|Release|all]"
job="default"
configurations="all"

while [ $# -gt 0 ];	do
    case "$1" in
		-j)  job="$2"; shift;;
		-c)  configurations="$2"; shift;;
		-*)
	    	echo >&2 \
	    		$usage
	    	exit 1;;
		*)  break;;
    esac
    shift
done

if ! [[ $job =~ ^[a-zA-Z0-9_\-]+$ ]]; then
	echo -e "*** Illegal job name specified: $job..."
	echo -e "    > Job names may only contain letters, numbers, dashes and underscores"
	echo
	exit 1
fi

if [ x"$configurations" != xDebug ] && [ x"$configurations" != xRelease ] && [ x"$configurations" != xall ]; then
	echo $usage
	exit 1
elif [ x"$configurations" = xall ]; then
	configurations="Debug Release"
fi

for config in $configurations; do
	echo "Building MoaiSample/moai/iphoneos for $config"
	xcodebuild -configuration $config -workspace MoaiSample.xcodeproj/project.xcworkspace -scheme moai -sdk iphoneos build CONFIGURATION_BUILD_DIR=/tmp/ios/$job/MoaiSample/moai/iphoneos/$config
	echo "Done. Binaries available in /tmp/ios/$job/MoaiSample/moai/iphoneos/$config"
	echo "Building MoaiSample/moai/iphonesimulator for $config"
	xcodebuild -configuration $config -workspace MoaiSample.xcodeproj/project.xcworkspace -scheme moai -sdk iphonesimulator build CONFIGURATION_BUILD_DIR=/tmp/ios/$job/MoaiSample/moai/iphonesimulator/$config
	echo "Done. Binaries available in /tmp/ios/$job/MoaiSample/moai/iphonesimulator/$config"
	echo "Building MoaiSample/moai-fmod/iphoneos for $config"
	xcodebuild -configuration $config -workspace MoaiSample.xcodeproj/project.xcworkspace -scheme moai-fmod -sdk iphoneos build CONFIGURATION_BUILD_DIR=/tmp/ios/$job/MoaiSample/moai-fmod/iphoneos/$config
	echo "Done. Binaries available in /tmp/ios/$job/MoaiSample/moai-fmod/iphoneos/$config"
	echo "Building MoaiSample/moai-fmod/iphonesimulator for $config"
	xcodebuild -configuration $config -workspace MoaiSample.xcodeproj/project.xcworkspace -scheme moai-fmod -sdk iphonesimulator build CONFIGURATION_BUILD_DIR=/tmp/ios/$job/MoaiSample/moai-fmod/iphonesimulator/$config
	echo "Done. Binaries available in /tmp/ios/$job/MoaiSample/moai-fmod/iphonesimulator/$config"
done