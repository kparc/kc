{
  "targets": [
    {
      "target_name": "shakti",
      "sources": [ "./shakti.c" ],
      "link_settings": {
        "conditions": [ [ "OS=='linux'", {"libraries":["-Wl,-rpath,'$$ORIGIN/../../'"]} ] ],
      },
    }
  ]
}
