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
              "src/activate-window/activate_window_win.cc",
              "src/user-activity/user_activity_win.cc"
          ],
      }],
      ['OS=="mac"', {
          "sources": [
              "src/checker.cc",
              "src/activate-window/activate_window.cc",
              "src/user-activity/user_activity_mac.cc"
          ],
      }],
      ['OS=="linux"', {
          "sources": [
              "src/checker.cc",
              "src/activate-window/activate_window.cc",
              "src/user-activity/user_activity_linux.cc"
          ],
          'variables': {
          	'pkg-config': 'pkg-config'
                },
          'direct_dependent_settings': {
              'cflags': [
                '<!@(<(pkg-config) --cflags x11 xext xscrnsaver)',
              ],
            },
            'link_settings': {
              'ldflags': [
                '<!@(<(pkg-config) --libs-only-other --libs-only-L x11 xext xscrnsaver)',
              ],
              'libraries': [
                '<!@(<(pkg-config) --libs-only-l x11 xext xscrnsaver)',
              ],
            },
      }],
    ]}
  ]
}
