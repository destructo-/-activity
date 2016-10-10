var exec = require('child_process').exec;
var fs = require('fs');

var archs = ['ia32', 'x64'];
run(archs);

function run(archs) {
  var arch = (archs && archs.length) ? archs[archs.length - 1] : null;
  if (arch !== null) {
	console.log(`activity ${arch} build...`);
	buildCommand(generateCommand(arch), () => {
		createFolder('./bin/binary');
		if (arch === 'ia32') {
			fs.rename('./build/Release/checker.node', './bin/binary/checker_x32.node', (err) => {
				if (err) {
				  console.log(err);	
				}				
			});
		} else {
			fs.rename('./build/Release/checker.node', './bin/binary/checker.node', (err) => {
				if (err) {
				  console.log(err);	
				}
			});
		}	
		console.log(`success build ${arch}`);
		var archsModified = archs.splice(0, archs.length -1);
		run(archsModified);
	});  
  }
}

function buildCommand(command, success) {
	exec(command, function(error, stdout, stderr) {	
    if (error !== null) {
        console.log('exec error: ' + error);
    } else {
		success();
	}
});
}

function createFolder(path) {
    const folder = path;
    if (!fs.existsSync(folder)) {
        try {
            fs.mkdirSync(folder);
        }
        catch (e) {
            if (!fs.statSync(folder).isDirectory()) {
                throw new Error(e);
            }
        }
    }
}

function generateCommand(arch) {
	var command = `node-gyp clean configure build --verbose	--target=1.4.0 --arch=${arch} --dist-url=https://atom.io/download/atom-shell`;
	return command;
}




//build.stdout.on('data', (data) => {
//	console.log('complete', data);
//});

//build.stderr.on('data', (data) => {
//	console.log('error', data);
//});

//node-gyp clean configure build --verbose --target=1.4.0 --arch=ia32
 //--dist-url=https://atom.io/download/atom-shell