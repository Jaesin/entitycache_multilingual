<?php
/**
 * @file
 * EntityCacheMLControllerHelper cache helper.
 */

/**
 * Class EntityCacheMLControllerHelper
 */
class EntityCacheMLControllerHelper extends EntityCacheControllerHelper {
  /**
   * @inheritdoc
   */
  public static function entityCacheGet($controller, $ids, $conditions = array()) {
    /** @var DrupalDefaultEntityController $controller */

    // Get items if they have already been cached.
    $cached_entities = parent::entityCacheGet($controller, $ids, $conditions);
    // Figure out which items are left.
    $missing_ids = array_diff($ids, array_keys($cached_entities));

    // If we have missing ids, we need to load and cache them.
    if (!empty($missing_ids)) {
      // Get the query for these entities.
      $query = $controller->buildQuery($ids, array());
      // Fetch all entities.
      $queried_entities = $query
        ->execute()
        ->fetchAllAssoc($controller->idKey);
      // check for results from the query.
      if (!empty($queried_entities)) {
        // Allow other modules to load their data into he entity before caching it.
        $controller->attachLoad($queried_entities);
        // Cache and add the queried entities.
        $cached_entities += self::entityCacheSet($controller, $queried_entities);;
      }
    }

    return $cached_entities;
  }

  /**
   * @inheritdoc
   */
  public static function entityCacheSet($controller, $entities) {
    // Use the language for this request.
    global $language;
    // Buffer cached results.
    $cached = array();
    // Cache all entities.
    foreach ($entities as $id => $item) {
      // Set the items cached language for matching the language later.
      $item->entitycache_language = $language->language;
      // Cache the entity.
      cache_set("{$item->{$controller->idKey}}_{$language->language}", $item, "cache_entity_{$controller->entityType}");
      // Add the item to the cache results.
      $cached["{$item->{$controller->idKey}}_{$language->language}"] = $item;
    }

    return $cached;
  }
}