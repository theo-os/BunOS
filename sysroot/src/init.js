import { CString, dlopen, FFIType, ptr, suffix } from "bun:ffi";

const encodeStr = (s) => {
	return ptr(new TextEncoder().encode(s));
};

const encodeStrArray = (sarr) => {
	const arr = new Float64Array(sarr.map(s => encodeStr(s)));

	return ptr(arr);
}

const { symbols: libc } = dlopen("libc.so.6", {
	execvp: {
		args: [FFIType.cstring, FFIType.ptr],
		returns: FFIType.i32,
	},
	fork: {
		args: [],
		returns: FFIType.i32,
	},
});

const serviceConfig = await import("./services.toml");

console.log("Hello from BunOS 🚀");

console.log(serviceConfig.default);

for (const service of serviceConfig.default.service) {
	console.log(`starting service ${service.name}`);


	//if (service.background) {
	const pid = libc.fork();
	if (pid == 0)
		libc.execvp(
			encodeStr(service.command[0]),
			encodeStrArray(service.command),
		);
	//} else libc.execvp(
	//encodeStr(service.command[0]),
	//encodeStrArray(service.command),
	//);
}

