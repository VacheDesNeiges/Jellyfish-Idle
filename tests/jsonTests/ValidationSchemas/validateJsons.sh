#!/bin/bash

jsonschema -i assets/jsons/abilities.json tests/jsonTests/ValidationSchemas/abilitiesSchema.json
jsonschema -i assets/jsons/achievements.json tests/jsonTests/ValidationSchemas/achievementsSchema.json
jsonschema -i assets/jsons/buildings.json tests/jsonTests/ValidationSchemas/buildingsSchema.json
jsonschema -i assets/jsons/cultures.json tests/jsonTests/ValidationSchemas/culturesSchema.json
jsonschema -i assets/jsons/jobs.json tests/jsonTests/ValidationSchemas/jobsSchema.json
jsonschema -i assets/jsons/multipliers.json tests/jsonTests/ValidationSchemas/multipliersSchema.json
jsonschema -i assets/jsons/recipes.json tests/jsonTests/ValidationSchemas/recipesSchema.json
jsonschema -i assets/jsons/ressources.json tests/jsonTests/ValidationSchemas/ressourcesSchema.json
jsonschema -i assets/jsons/upgrades.json tests/jsonTests/ValidationSchemas/upgradesSchema.json