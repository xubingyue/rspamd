#ifndef CLASSIFIERS_H
#define CLASSIFIERS_H

#include "config.h"

/* Consider this value as 0 */
#define ALPHA 0.0001

struct rspamd_classifier_config;
struct rspamd_task;

/* Common classifier structure */
struct classifier_ctx {
	rspamd_mempool_t *pool;
	GHashTable *results;
	gboolean debug;
	struct rspamd_classifier_config *cfg;
};

struct classifier {
	char *name;
	struct classifier_ctx * (*init_func)(rspamd_mempool_t *pool,
		struct rspamd_classifier_config *cf);
	gboolean (*classify_func)(struct classifier_ctx * ctx,
		GTree *input, struct rspamd_task *task,
		lua_State *L);
	gboolean (*learn_spam_func)(struct classifier_ctx * ctx,
		GTree *input, struct rspamd_task *task, gboolean is_spam, lua_State *L,
		GError **err);
};

/* Bayes algorithm */
struct classifier_ctx * bayes_init (rspamd_mempool_t *pool,
	struct rspamd_classifier_config *cf);
gboolean bayes_classify (struct classifier_ctx * ctx,
	GTree *input,
	struct rspamd_task *task,
	lua_State *L);
gboolean bayes_learn_spam (struct classifier_ctx * ctx,
	GTree *input,
	struct rspamd_task *task,
	gboolean is_spam,
	lua_State *L,
	GError **err);

#endif
/*
 * vi:ts=4
 */