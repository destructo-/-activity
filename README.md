# -activity

# on windows:
```
npm install --global node-gyp
```
run cmd as admin
```
npm install --global --production windows-build-tools
```

# on linux
```
sudo apt-get install libxss-dev
```

# build native node module
restart cmd (it's windows baby)
```
node-gyp configure
node-gyp build
```

# build native electrone module
restart cmd too
- clone electrone repo
```
set HOME=C:\{path to electron repo}\electron-gyp
node-gyp clean configure build --verbose --target={1.4.0 or other versions} --arch={can be ia32 or x64} --dist-url=https://atom.io/download/atom-shell
```
get build file from
```
-activity/build/Release/checker.node
```

