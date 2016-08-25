{
  "targets": [
    {
      "target_name": "checker",
      "sources": [
        "src/checker.cc",
        "src/user-activity/user_activity.cc",
        "src/activate-window/activate_window.cc"
      ],
      "include_dirs": [ "<!(node -e \"require('nan')\")" ]
    }
  ]
}
