#!/bin/sh
set -ex

BUN_VERSION="${BUN_VERSION:-"bun-v0.1.4"}"

mkdir -p build sysroot/bin

if [ ! -f "sysroot/bin/bun" ]; then
	curl -L \
		-o build/bun-linux-x64.zip \
		"https://github.com/oven-sh/bun/releases/download/${BUN_VERSION}/bun-linux-x64.zip"

	unzip build/bun-linux-x64.zip -d build/bun
	cp build/bun/bun-linux-x64/bun ./sysroot/bin/
fi

./scripts/copy-libs.sh

