{
  "targets": [
    {
    "target_name": "checker",
    "include_dirs": [ "<!(node -e \"require('nan')\")" ],
    "sources": [],
    'conditions': [
      ['OS=="win"', {
          "sources": [
              "src/checker.cc",
              "src/activate-window/activate_window.cc",
              "src/user-activity/user_activity.cc"
          ],
      }],
    ]}
  ]
}