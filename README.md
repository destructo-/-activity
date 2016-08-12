# -activity 

# on windows:
```
npm install --global node-gyp
```
run cmd as admin
```
npm install --global --production windows-build-tools
```

# build native nide module
restart cmd (it's windows baby) 
```
node-gyp configure
node-gyp build
```

# build native electrone module
restart cmd too
- clone electrone repo
```
set HOME=C:\{path to electron repo}\.electron-gyp 
node-gyp rebuild --target=<1.3.3 or other versions> --dist-url=https://atom.io/download/atom-shell
```
get build file from
```
-activity/build/Release/checker.node
```

