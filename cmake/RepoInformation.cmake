include(GitInformation)

if(GIT_FOUND)
	git_check_repository(GIT_REPO_FOUND)
	if(GIT_REPO_FOUND)
		git_commit_hash(GIT_COMMIT_HASH GIT_COMMIT_HASH_SHORT)
		git_branch_name(GIT_BRANCH)
		message(STATUS "git branch: ${GIT_BRANCH}")
		message(STATUS "git commit hash: ${GIT_COMMIT_HASH}")

		# version handling if repository information is available
		git_head_tag(GIT_HEAD_TAG)
		message(STATUS "git head tag: ${GIT_HEAD_TAG}")
		if("${GIT_HEAD_TAG}" STREQUAL "")
			set(PROJECT_VERSION "${PROJECT_VERSION}-${GIT_COMMIT_HASH_SHORT}")
		elseif(NOT ("${GIT_HEAD_TAG}" MATCHES "[v]?[0-9]+\..*"))
			set(PROJECT_VERSION "${PROJECT_VERSION}-${GIT_HEAD_TAG}")
		endif()
	else()
		message(STATUS "no git repository found, no further version info available")
	endif()
else()
	message(STATUS "git not found, no further version info available")
endif()
message(STATUS "Project Version: ${PROJECT_VERSION}")
