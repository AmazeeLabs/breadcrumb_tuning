<?php

/**
 * @file
 * See plugin description.
 */

$plugin = array(
  'title' => t('Breadcrumbs tuned (with fallback to Crumbs)'),
  'single' => TRUE,
  'description' => t('Shows tuned breadcrumbs (if they have been tuned), or crumbs (if module exists), or standard breadcrumbs.'),
  'category' => t('Page elements'),
  'render last' => TRUE,
);

/**
 * Render callback.
 */
function breadcrumb_tuning_breadcrumbs_tuned_content_type_render($subtype, $conf, $panel_args) {
  list($matched_rule) = _breadcrumb_tuning_get();
  if (empty($matched_rule['actions']['set-breadcrumbs']['breadcrumbs']) && module_exists('crumbs')) {
    $content = crumbs()->page->breadcrumbHtml;
  }
  else {
    $content = theme('breadcrumb', array('breadcrumb' => drupal_get_breadcrumb()));
  }
  return (object) array(
    'content' => $content,
    'css_class' => 'pane-page-breadcrumb',
  );
}
