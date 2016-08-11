{
  "targets": [
    {
      "target_name": "checker",
      "sources": [ "src/checker.cc" ],
      "include_dirs": [ "<!(node -e \"require('nan')\")" ]
    }
  ]
}
