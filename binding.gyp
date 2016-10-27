{
  "targets": [
    {
      "target_name": "checker",
      "sources": [ 
		"src/checker.cc",
		"src/activate-window/activate_window.cc",
		"src/user-activity/user_activity.cc"
	  ],
      "include_dirs": [ "<!(node -e \"require('nan')\")" ]
    }
  ]
}
