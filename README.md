# Breadcrumb tuning

A Drupal module that helps you win the fight with the breadcrumb configuration.

It can be used alone, but it also can work together with other breadcrumb modules.

After installing, see the `admin/config/search/breadcrumb_tuning` path for configuration help.

## How it works

TBD

## <a name="pane"></a> The "Breadcrumbs tuned (with fallback to Crumbs)" pane

The pane does the followong:

```
if (there is a matched rule for the current page) {
  show the default breadcrumbs (possibly, altered/replaced by the module)
}
else {
  if (Crumbs module enabled) {
    show Crumbs breadcrumbs
  }
  else {
    show default breadcrumbs
  }
}
```

## Todo

- don't calculate breadcrumbs in hook_init()
