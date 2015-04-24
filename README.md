Entitycache Multilingual
========================

The is a Drupal module to extend the [entitycache module](http://drupal.org/project/entitycache) allowing a seperate cache per language.

## When to use this module
When modules attach setting and content to a module, they sometime handle localization in different ways resulting in unpredictable cache results when view entities in different languages. This module can help by adding a cached version of each language.

## Dependencies
Of course this mofule depends on the [entitycache module](http://drupal.org/project/entitycache) but as of April, 2015  it also depends on [this patch](https://www.drupal.org/node/2476309#comment-9860297).

## Configuration
There is no UI for this module, if you enable it, it will start caching by language. You can disable specific core entity types by setting the "entitycache_multilingual_disabled_entity_types" variable with drush lke with entitycache. 

i.e.
```
 # drush vset --format=json entitycache_multilingual_disabled_entity_types '["file", "user"]'
```

##### Attribution
Some code copied from [@drasgardian](http://drupal.org/u/drasgardian)'s patch [cache per language](http://drupal.org/node/1851430) on [D.O.](http://drupal.org).
