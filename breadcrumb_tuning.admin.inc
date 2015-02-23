<?php

/**
 * Configuration form callback.
 */
function breadcrumb_tuning_admin_form($form, &$form_state) {
  $form['warning']['#markup'] = t('WARNING: only JSON syntax is validated automatically! The config structure is not validated! Be careful. Use API ans Example.<br />
While there is no normal UI, you can use !link for a better editing experience.', array('!link' => l('jsoneditoronline.org', 'https://www.jsoneditoronline.org/?json=%7B%7D', array('attributes' => array('target'=>'_blank')))));

  $form['config'] = array(
    '#type' => 'textarea',
    '#title' => t('Config'),
    '#description' => t('Use JSON to describe the module configuration. See the API and Example sections for help.'),
    '#default_value' => variable_get('breadcrumb_tuning_config_json'),
    '#attributes' => array(
      'style' => 'font-family: monospace;',
    ),
    '#rows' => 10,
  );
  $form['debug'] = array(
    '#type' => 'checkbox',
    '#title' => t('Debug mode'),
    '#description' => t('The debug mode uses dpm() function. So, to see the debug messages, you need to have the Devel module enabled and the user account should have "Access developer information" permission.'),
    '#default_value' => variable_get('breadcrumb_tuning_debug'),
  );
  $form['clear_menu_cache'] = array(
    '#type' => 'checkbox',
    '#title' => t('Clear menu cache.'),
    '#description' => t('Menu active trails are cached per page. If you added/changed/deleted the set-active-trail-path action, you should clear menu cache.'),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  $module_path = drupal_get_path('module', 'breadcrumb_tuning');
  $form['api'] = array(
    '#type' => 'fieldset',
    '#title' => t('API'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    'api' => array(
      '#markup' => '<pre>' . file_get_contents($module_path . '/breadcrumb_tuning.config.api.json') . '</pre>',
    ),
  );
  $form['example'] = array(
    '#type' => 'fieldset',
    '#title' => t('Example'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    'example' => array(
      '#markup' => '<pre>' . file_get_contents($module_path . '/breadcrumb_tuning.config.example.json') . '</pre>',
    ),
  );

  // The system_settings_form() is not used to avoid per-domain configuration.
  return $form;
}

/**
 * Validation handler for the configuration form.
 */
function breadcrumb_tuning_admin_form_validate(&$form, &$form_state) {
  if (drupal_json_decode($form_state['values']['config']) === NULL) {
    form_error($form['config'], t('Please provide valid config.'));
  }
}

/**
 * Submit handler for the configuration form.
 */
function breadcrumb_tuning_admin_form_submit(&$form, &$form_state) {
  variable_set('breadcrumb_tuning_config', drupal_json_decode($form_state['values']['config']));
  variable_set('breadcrumb_tuning_config_json', $form_state['values']['config']);
  variable_set('breadcrumb_tuning_debug', $form_state['values']['debug']);
  drupal_set_message(t('The configuration options have been saved.'));
  if (!empty($form_state['values']['clear_menu_cache'])) {
    menu_cache_clear_all();
  }
}
